#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template <class T>
class CacheManager{

    int capacity;
    map<string, pair <T , int>> cache_data; // <Clave , <Obj , Indice de Uso >>

    bool write_file (string, T); // NT: ?

    public:
    CacheManager(int); // Constructor, recibe la capacidad en el int
    ~CacheManager(); //Dest.

    void insert(string key, T obj);
    T get(string key);

// Agregar todas las funciones necesarias
};


//NT: Sobre uso de templates, esencialmente es lo que permite que una función acepte tipos de forma dinámica
//Es decir, un objeto T en vez de un tipo particular.
template <class T>
CacheManager<T>::CacheManager(int cap){
    capacity = cap;
}

template <class T>
CacheManager<T>::~CacheManager(){}

template <class T>
bool CacheManager<T>::write_file(string key, T obj){
      //Create and open a text file
      //NT: En teoría, si el archivo ya existe lo utiliza. Sino, lo crea. Verificar si esto funciona asi.
      ofstream MyFile("cache.txt");
      MyFile.write((char*)&obj, sizeof(obj));
      MyFile.close();
      return true;
 }

 //INSERT
template <class T>
void CacheManager<T>::insert(string key, T obj){
   this->cache_data.insert(make_pair(key, obj));
   this->write_file(key, obj);
}

//GET / Find by key
template <class T>
T CacheManager<T>::get(string key){
    return this->cache_data.find(key);
}
