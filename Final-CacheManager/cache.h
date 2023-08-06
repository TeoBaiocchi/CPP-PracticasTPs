#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>
#include <vector>

using namespace std;

template <class T>
class CacheManager
{
    // El dios que vive en mi computadora me dijo que hiciera esto para evitar un warning porque el metodo size retorna un unsigned. Lo peor es que lo solucionó el problema
    size_t capacity;

    unsigned int indice = 1;              // La variable indice unicamente va a aumentar con cada operación, por lo que es conveniente disponer de ella como un contador propio de la clase
    map<string, pair<T, int>> cache_data; // <Clave , <Obj , Indice de Uso>> El indice de uso se usa para obtener el LRU

    //Cuando se inserte el primer elemento a la caché, se asignará un nombre para generar el archivo en memoria y usar de manera generalizada.
    string cacheFileName;

    // Cadena que separará los indices del objeto al momento de escribir en memoria
    // Importante que quede como salto de linea porque hay funciones hechas en torno a eso
    string separadorKeyObj = "\n";

public:
    CacheManager(int);
    ~CacheManager();


    void insert(string key, T obj);
    T get(string key);
    string getKeyLRU();
    void show_cache();

    void generarArchivoTest(T);

private:

    bool existeKeyEnMemoria(string);
    ifstream encontrarEnMemoria(string);

    bool write_file(string, T, string);
    void limpiarMemoria();

    void actualizarEnMemoria(string, T);
    void persistirEnCacheyMemoria(string, T);
};

template <class T>
CacheManager<T>::CacheManager(int cap)
{
    this->capacity = cap;
}

template <class T>
CacheManager<T>::~CacheManager(){}


template <class T>
void CacheManager<T>::show_cache()
{
    cout << "- - - - - - - - - - - - - - - - - - -" << endl
         << " -> Imprimiendo contenido de cache <-" << endl
         << "{";
    for (const auto &x : cache_data)
    {
        cout << endl
             << " [ID " << x.first << " - Indice Uso: " << x.second.second << "]";
        cout << "-> ";
        cout << x.second.first;
        // Asumimos sobrecargado el operador para mostrar la clase, pero de no ser el caso, usaríamos el print que debe incluir.
    }
    cout << "} - - - - - - - - - - - - - - - - - -" << endl;
}




template <class T>
void CacheManager<T>::insert(string key, T obj)
{
    if (cache_data.size() == 0)
    {   //En caso de que sea la primer inserción, asignamos el nombre de archivo y nos aseguramos de que esté limpio de resiudos
        this->cacheFileName = "cache_" + obj.class_name + ".txt";
        limpiarMemoria();
    }

    // Primero revisamos si se trata de una key existente para ver si es una actualizacion o una insercion plana
    // No podemos evitar revisar el archivo por la existencia de la key, ya que en caso de no estar en la cache, puede aun estar tratandose de actualizar un objeto que exista guardado en memoria.
    if (existeKeyEnMemoria(key))
    {
        cout << "Existe en el archivo" << endl;
        auto it = cache_data.find(key);
        if (it == cache_data.end())
        {
            cout << "Pero no en la cache" << endl;
            // Si se da que existe, pero no esta en cache, lo traemos con get.
            get(key);
            it = cache_data.find(key);
        }
        it->second = make_pair(obj, indice);            // El indice ya es incrementado por get.
        actualizarEnMemoria(key, obj);      //Es necesario también actualizar su referencia en memoria
        return;
    }

    persistirEnCacheyMemoria(key, obj);
}




template <class T>
void CacheManager<T>::persistirEnCacheyMemoria(string key, T obj){
    if (cache_data.size() >= capacity)
    { // En caso de que la capacidad sea alcanzada, borramos el LRU antes de realizar la inserción.
    string keyLRU = getKeyLRU();
    cache_data.erase(cache_data.find(keyLRU));
    }
    cache_data.insert(make_pair(key, make_pair(obj, indice++)));
    write_file(key, obj, this->cacheFileName);
}




template <class T>
T CacheManager<T>::get(string key)
{
    T obj; // Asumimos que la clase va a tener un constructor vacio, de lo contrario esto no es posible
    auto it = cache_data.find(key);
    if (it != cache_data.end())
    {
        // Al encontrarlo también actualizamos su valor de acceso, como indica el ejemplo.
        cache_data[key] = make_pair(cache_data[key].first, indice++);
        obj = cache_data[key].first;
        return obj;
    }

    //En caso de no encontrarse en cache.
    ifstream archivo = encontrarEnMemoria(key);
    cout << "No me rompi abriendo el fstream" << endl;
    if (!archivo.eof())
    {
        archivo.read(reinterpret_cast<char *>(&obj), sizeof(T));
        cout << "Si bro, lei el objeto y es " << obj;
        persistirEnCacheyMemoria(key, obj); // Insert se va a encargar de traerlo a memoria y actualizar su indice
    }
    else
    {
        perror("ERROR: Se intento acceder a un elemento inexistente - ");
    }
    archivo.close();
    return obj;
}



template <class T>
bool CacheManager<T>::write_file(string key, T obj, string nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::out | ios::binary);
    archivo << key << this->separadorKeyObj;
    archivo.write(reinterpret_cast<char * const>(&obj), sizeof(T));
    archivo << endl;
    archivo.close();
    return true;
}


template <class T>
void CacheManager<T>::generarArchivoTest(T obj){
    string nombreArchivo = "individual.txt";
    ofstream archivo(nombreArchivo, ios::out | ios::binary);
    archivo.write(reinterpret_cast<char * const>(&obj), sizeof(T));
    archivo.close();
    T leido;
    ifstream lectura(nombreArchivo, ios::in | ios::binary);
    lectura.read(reinterpret_cast<char * const>(&leido), sizeof(T));
    cout << leido << endl;
    archivo.close();
}




template <class T>
ifstream CacheManager<T>::encontrarEnMemoria(string key)
{
    string linea;

    ifstream archivo(this->cacheFileName, ios::in | ios::binary);

    for (int lineaNro = 0; getline(archivo, linea); lineaNro++)
    {
        if (lineaNro % 2 == 0 && linea == key){ // En las lineas pares se guardan las keys
            getline(archivo, linea);
            break;
        }
    }
    return archivo;
}




template <class T>
bool CacheManager<T>::existeKeyEnMemoria(string key)
{
    string linea;
    ifstream archivo(this->cacheFileName, ios::in | ios::binary);

    for (int lineaNro = 0; getline(archivo, linea); lineaNro++)
    {
        if (lineaNro % 2 == 0 && linea == key){ // En las lineas pares se guardan las keys
            return true;
        }
    }
    return false;
}




template <class T>
void CacheManager<T>::actualizarEnMemoria(string key, T obj)
{
    T objAux;
    vector<string> indices;
    vector<T> objetos;
    string linea;

    //Copio el contenido del archivo
    ifstream archivo((this->cacheFileName), ios::in | ios::binary);
    cout << "LECTURA DE ARCHIVO: " << endl;
    for (int lineaNro = 0; getline(archivo, linea); lineaNro++)
    {
            if(lineaNro % 2 == 0){
                indices.push_back(linea);
            } else {
                archivo.read(reinterpret_cast<char * const>(&objAux), sizeof(T));
                objetos.push_back(objAux);
            }
    }
    archivo.close();

    //Limpio el archivo
    remove(this->cacheFileName.c_str());

    //Vuelvo a armar el archivo, omitiendo el indice desactualizado
    for(int i = 0; i < indices.size(); i++){
        cout << "OBJETO : " << indices[i] << " " << objetos[i];
        if(indices[i] != key){
            cout << " (VALIDADO)" << endl;
            write_file(indices[i], objetos[i], this->cacheFileName);
        }
    }

    //Finalmente agrego el valor actualizado
    write_file(key, obj, this->cacheFileName);
}




template <class T>
string CacheManager<T>::getKeyLRU()
{
    int menor = indice;
    string keyActual;
    for (const auto &x : cache_data)
    {
        if (x.second.second < menor)
        {
            menor = x.second.second; // indice de uso
            keyActual = x.first;     // key
        }
    }
    return keyActual;
}




template <class T>
void CacheManager<T>::limpiarMemoria()
{
    remove(this->cacheFileName.c_str());
    return;
}
