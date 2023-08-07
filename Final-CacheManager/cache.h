#include "clasePersistencia.h"
#include "memoria.h"

using namespace std;

template <class T>
class CacheManager
{
    size_t capacity;

    unsigned int indice = 1;              // La variable indice unicamente va a aumentar con cada operación, por lo que es conveniente disponer de ella como un contador propio de la clase
    map<string, pair<T, int>> cache_data; // <Clave , <Obj , Indice de Uso>> El indice de uso se usa para obtener el LRU

    //Cuando se inserte el primer elemento a la caché, se asignará un nombre para generar el archivo en memoria y usar de manera generalizada.
    string cacheFileName;


public:
    MemoriaManager<T> mm;
    CacheManager(int);
    ~CacheManager();

    //Permite guardar en cache (y en memoria) un objeto con una llave
    void insert(string key, T obj);

    //Dada una key obtiene el objeto, si existe. Primero revisa en cache, luego en memoria. De no existir devuelve un objeto vacio de indice ""
    T get(string key);

    //Retorna la key a la que le corresponda el menor indice de la caché.
    string getKeyLRU();

    //Print()
    void show_cache();

private:

    //Funcion interna utilizada por insert para efectuar la inserción.
    void persistirEnCacheyMemoria(string, T);

    void logger(string msg){
        cout << "Log CacheManager: " << msg << endl;
    }
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
    {
        //Si se trata de la primera inserción de nuestra caché, generamos el nombre que tendra la memoria
        //y generamos el manejador que se encargará de todas las llamadas posteriores a memoria.
        this->cacheFileName = "cache_" + obj.class_name + ".dat";
        MemoriaManager<T> mm1(this->cacheFileName);
        this->mm = mm1;
        mm.limpiarMemoria();
    }

    // Primero revisamos si se trata de una key existente para ver si es una actualizacion o una insercion plana
    // No podemos evitar revisar el archivo por la existencia de la key, ya que en caso de no estar en la cache, puede aun estar tratandose de actualizar un objeto que exista guardado en memoria.
    if (mm.existeKey(key))
    {
        auto it = cache_data.find(key);
        if (it == cache_data.end())
        {
            get(key);                       // Si se da que existe, pero no esta en cache, lo traemos con get.
            it = cache_data.find(key);
        }
        it->second = make_pair(obj, indice); // El indice ya es incrementado por get.
        mm.actualizar(key, obj);            //Es necesario también actualizar su referencia en memoria
        return;
    }

    //Si no se trata de una actualización, realizamos la inserción estandar
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
    mm.write_file(key, obj);
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

    //En caso de no encontrarse en cache, revisamos si existe en memoria
    if(mm.existeKey(key)){
            obj = mm.obtenerByKey(key);
            persistirEnCacheyMemoria(key, obj); // Este metodo se va a encargar de traerlo a memoria y actualizar su indice
    } else {
        cout << "ERROR: Se intento acceder a un objeto de indice inexistente. " << endl;
    }

    return obj;
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








