#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

template <class T>
class MemoriaManager
{
    string memoriaFileName;
public:

     MemoriaManager();
     MemoriaManager(string);
    ~MemoriaManager();

    //Dada una key y un objeto, lo inserta en memoria. Si no se aclara un archivo, se usara memoriaFileName
    void write_file(string, T);
    void write_file(string, T, string);

    //Dada una key y un objeto, actualiza su valor en memoria.
    //Para lograr esto, copia todo el contenido del archivo original en uno nuevo, exceptuando el objeto a actualizar
    //De esta forma, dejamos atrás el valor original y realizamos un write file con el valor actualizado.
    bool actualizar(string, T);

    //Revisa la memoria y devuelve segun la existencia de una key
    bool existeKey(string key);

    //Dada una key, itera hasta encontrar un objeto con esa misma key. De no existir, deberia devolver T vacio y mostrar una advertencia
    T obtenerByKey(string key);

    //Regenerar el archivo en limpio.
    void limpiarMemoria();

    void imprimirMemoria();

    ClaseDePersistencia<T> obtenerPersistenciaByKey(string);

    private:
        void logger(string msg){
        cout << "Log MemoryManager: " << msg << endl;
    }
};

template <class T>
MemoriaManager<T>::MemoriaManager(){}

template <class T>
MemoriaManager<T>::MemoriaManager(string memoriaFileName)
{
    this->memoriaFileName = memoriaFileName;
}

template <class T>
MemoriaManager<T>::~MemoriaManager(){}




template <class T>
void MemoriaManager<T>::write_file(string key, T obj){
    return write_file(key, obj, this->memoriaFileName);
}
template <class T>
void MemoriaManager<T>::write_file(string key, T obj, string fileName){
    ofstream archivo(fileName, ios::out | ios::binary);
    ClaseDePersistencia<T> c(key, obj);
    archivo.write(reinterpret_cast<char * const>(&c), sizeof(ClaseDePersistencia<T>));
    obj.print();
    archivo.close();
}



template <class T>
bool MemoriaManager<T>::actualizar(string indice, T obj){
    T objAux;
    vector<ClaseDePersistencia<T>> datos;
    ClaseDePersistencia<T> c;

    //Vuelco el contenido de la memoria en los vectores, exceptuando el objeto a actualizar
    ifstream archivo((this->memoriaFileName), ios::in | ios::binary);
    while(archivo && !archivo.eof()){
        archivo.read(reinterpret_cast<char * const>(&c), sizeof(ClaseDePersistencia<T>));
        if(c.key != indice)
            datos.push_back(c);
    }
    archivo.close();

    //Limpio el archivo
    remove(this->memoriaFileName.c_str());

    //Vuelvo a generar el archivo con el contenido del vector
    for(ClaseDePersistencia<T> dato : datos){
        write_file(dato.key, dato.dato);
    }

    //Finalmente agrego el valor actualizado
    write_file(indice, obj);
}

template <class T>
bool MemoriaManager<T>::existeKey(string indice){
    ClaseDePersistencia<T> c;
    ifstream archivo((this->memoriaFileName), ios::in | ios::binary);
     while(archivo && !archivo.eof()){
        archivo.read(reinterpret_cast<char * const>(&c), sizeof(ClaseDePersistencia<T>));
        if(c.key == indice){
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

template <class T>
T MemoriaManager<T>::obtenerByKey(string indice){
    T obj;
    ClaseDePersistencia<T> c;
    ifstream archivo((this->memoriaFileName), ios::in | ios::binary);
     while(archivo && !archivo.eof()){
        archivo.read(reinterpret_cast<char *>(&c), sizeof(ClaseDePersistencia<T>));
        if(c.key == indice){
            obj = c.dato;
        }
    }
    archivo.close();
    return obj;
}

template <class T>
ClaseDePersistencia<T> MemoriaManager<T>::obtenerPersistenciaByKey(string indice){
    ifstream archivo(this->memoriaFileName, ios::in | ios::binary);
    ClaseDePersistencia<T> obj;
    while (archivo && !archivo.eof()){
        archivo.read(reinterpret_cast<char *>(&obj), sizeof(ClaseDePersistencia<T>));
        if(obj.key == indice)
            break;
        obj.key = "";
    }
    archivo.close();
    return obj;
}

template <class T>
void MemoriaManager<T>::limpiarMemoria(){
    remove(this->memoriaFileName.c_str());
}


template <class T>
void MemoriaManager<T>::imprimirMemoria(){
    ClaseDePersistencia<T> c;
    ifstream archivo((this->memoriaFileName), ios::in | ios::binary);
     while(archivo && !archivo.eof()){
        archivo.read(reinterpret_cast<char *>(&c), sizeof(ClaseDePersistencia<T>));
        cout << "Leyendo memoria: " << c.dato << endl;
    }
    archivo.close();
}



