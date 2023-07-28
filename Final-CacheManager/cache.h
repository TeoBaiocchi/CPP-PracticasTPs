#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template <class T>
class CacheManager{
    int capacity;
    map<string, pair <T , int>> cache_data; // <Clave , <Obj , Indice de Uso>> El indice de uso se usa para obtener el LRU
    string cacheFileName;
    bool write_file (string, T);
    void clear_file();

    public:
    CacheManager(int, string);
    ~CacheManager();

    void insert(string key, T obj);
    T get(string key);

// Agregar todas las funciones necesarias
};


//NT: Sobre uso de templates, esencialmente es lo que permite que una función acepte tipos de forma dinámica. Es decir, un objeto T en vez de un tipo particular.
template <class T>
CacheManager<T>::CacheManager(int cap, string cacheFileName){
    this->capacity = cap;
    this->cacheFileName = cacheFileName;
    this->clear_file();
}

template <class T>
CacheManager<T>::~CacheManager(){}

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


 //INSERT
template <class T>
void CacheManager<T>::insert(string key, T obj){
   this->cache_data.insert(make_pair(key, make_pair(obj, 0)));
   //TODO algoritmo que reemplace
   this->write_file(key, obj);
}

//GET / Find by key
template <class T>
T CacheManager<T>::get(string key){
    return this->cache_data.find(key);
}
