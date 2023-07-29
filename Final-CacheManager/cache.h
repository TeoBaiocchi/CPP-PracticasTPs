#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template <class T>
class CacheManager{
    int capacity;
    int indice = 1;
    map<string, pair<T , int>> cache_data; // <Clave , <Obj , Indice de Uso>> El indice de uso se usa para obtener el LRU
    string cacheFileName;
    bool write_file (string, T);
    void clear_file();

    public:
    CacheManager(int, string);
    ~CacheManager();

    void insert(string key, T obj);
    T get(string key);

// Agregar todas las funciones necesarias
    void show_cache();
    string getKeyLRU();
};



//Constructor - Destructor ----->
template <class T>
CacheManager<T>::CacheManager(int cap, string cacheFileName){
    this->capacity = cap;

    //NT: Agregué estas dos lineas ->
    this->cacheFileName = cacheFileName;
    this->clear_file();
}

template <class T>
CacheManager<T>::~CacheManager(){}
//<-----



// Print ----->
template <class T>
void CacheManager<T>::show_cache(){
    cout << "---------------" << endl << "Imprimiendo contenido de cache" << endl << "{";
    for(const auto &x: cache_data){
            cout << endl << " [ID "<< x.first << " - Indice Uso: " << x.second.second <<"]";
            cout << "-> "; x.second.first.print();
            //NT: CUIDADO! Esto asume que el tipo T tiene un metodo print. No se como imprimirlo genericamente sino...
    }
    cout << "}" << endl;
}
// <-----



 //INSERT ----->
template <class T>
void CacheManager<T>::insert(string key, T obj){

   if(cache_data.find(key) != cache_data.end()){
        //Si se encuentra el elemento que se esta tratando de insertar se trata de una actualización.
        cache_data[key] = make_pair(obj, indice++);
        //no entiendo por qué da error
        //return;
   }


   if(cache_data.size() >= capacity){
        //En caso de que la capacidad sea alcanzada, borramos el LRU antes de realizar la inserción.
        string keyLRU = getKeyLRU();
        cout << "borrando a " << keyLRU << endl;
        cache_data.erase(cache_data.find(keyLRU));
   }
    cout << "insertando a " << key << endl;
    cache_data.insert(make_pair(key, make_pair(obj, indice++)));
    write_file(key, obj);
}
//<-----


//GET/Find by key ----->
template <class T>
T CacheManager<T>::get(string key){
    auto it = cache_data.find(key);
    if(it != cache_data.end()){ //Es decir, si se encuentra el elemento antes del fin del map
        //Al encontrarlo también actualizamos su valor de acceso, como indica el ejemplo.
        cache_data[key] = make_pair(cache_data[key].first, ++indice);
        return cache_data[key];
    }
    return NULL; //TO DO: aca es donde al no encontrarse debería irse a memoria a buscarlo y devolver error si no está
}
// <-----


template <class T>
string CacheManager<T>::getKeyLRU(){
    int menor = indice;
    string keyActual;
    for(const auto &x: cache_data){
            if(x.second.second < menor){
                menor = x.second.second; //indice de uso
                keyActual = x.first;          //key
            }
        }
    return keyActual;
}




//Manejo de archivos ----->
//Incompleto, debido a mi escaso entendimiento y falta de atención. Esto es apenas
//un esqueleto de lo que hay que hacer. Falta investigar toda la lectura y corroborar que esto siquiera esté bien
template <class T>
bool CacheManager<T>::write_file(string key, T obj){
      ofstream archivo(this->cacheFileName, ios::app);
      archivo.write(reinterpret_cast<const char *>(&obj), sizeof(T));
      archivo.close();
      return true;
 }

 template <class T>
void CacheManager<T>::clear_file(){
      ofstream archivo(this->cacheFileName, ios::trunc);
      archivo.close();
      return;
 }
