#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>

using namespace std;

template <class T>
class CacheManager
{
    size_t capacity; // El dios que vive en mi computadora me dijo que hiciera esto para evitar un warning porque el metodo size retorna un unsigned. Lo peor es que lo solucionó el problema
    int indice = 1;
    map<string, pair<T, int>> cache_data; // <Clave , <Obj , Indice de Uso>> El indice de uso se usa para obtener el LRU
    string cacheFileName;
    string separadorKeyObj = "\n"; // Importante que quede como salto de linea porque hay funciones hechas en torno a eso

public:
    CacheManager(int);
    ~CacheManager();

    void insert(string key, T obj);
    T get(string key);

    void show_cache();

private:
    string getKeyLRU();
    bool write_file(string, T);
    fstream encontrarEnArchivo(string);
    void clear_file();
};

template <class T>
CacheManager<T>::CacheManager(int cap)
{
    this->capacity = cap;
}

template <class T>
CacheManager<T>::~CacheManager() {}

template <class T>
void CacheManager<T>::show_cache()
{
    cout << "---------------" << endl
         << "Imprimiendo contenido de cache" << endl
         << "{";
    for (const auto &x : cache_data)
    {
        cout << endl
             << " [ID " << x.first << " - Indice Uso: " << x.second.second << "]";
        cout << "-> ";
        cout << x.second.first;
        // Asumimos sobrecargado el operador para mostrar la clase
    }
    cout << "}" << endl;
}

template <class T>
void CacheManager<T>::insert(string key, T obj)
{

    if (cache_data.size() == 0)
    {
        // Mientras la cache este vacia, no se genera un archivo en disco, sino que este se crea
        // al momento del primer insert haciendo uso del classname que sabemos debe tener la clase T
        this->cacheFileName = "cache_" + obj.class_name + ".txt";
        clear_file();
    }

    // Primero revisamos si se trata de una key existente para ver si es una actualizacion o una insercion plana
    fstream archivo = encontrarEnArchivo(key);
    if (!archivo.eof())
    {
        // No podemos evitar revisar el archivo por la existencia de la key, ya que en caso de no estar en la cache, puede aun estar tratandose de actualizar un objeto que exista guardado en memoria.
        auto it = cache_data.find(key);
        if (it == cache_data.end())
        {
            // Si se da que existe, pero no esta en cache, lo traemos con get.
            get(key);
            it = cache_data.find(key);
        }
        it->second = make_pair(obj, indice);                      // El indice ya es incrementado por get.
        archivo.write(reinterpret_cast<char *>(&obj), sizeof(T)); // TO DO: Revisar
        archivo.close();
        return;
    }

    if (cache_data.size() >= capacity)
    {
        // En caso de que la capacidad sea alcanzada, borramos el LRU antes de realizar la inserción.
        string keyLRU = getKeyLRU();
        cout << "borrando a " << keyLRU << endl;
        cache_data.erase(cache_data.find(keyLRU));
    }

    cout << "insertando a " << key << endl;
    cache_data.insert(make_pair(key, make_pair(obj, indice++)));
    write_file(key, obj);
}

template <class T>
T CacheManager<T>::get(string key)
{
    T obj; // Asumimos que la clase va a tener un constructor vacio, de lo contrario esto no es posible
    auto it = cache_data.find(key);
    if (it != cache_data.end())
    { // Es decir, si se encuentra el elemento antes del fin del map
        // Al encontrarlo también actualizamos su valor de acceso, como indica el ejemplo.
        cache_data[key] = make_pair(cache_data[key].first, indice++);
        obj = cache_data[key].first;
        return obj;
    }

    fstream archivo = encontrarEnArchivo(key);
    if (!archivo.eof())
    {
        archivo.read(reinterpret_cast<char *>(&obj), sizeof(T));
        insert(key, obj); // Insert se va a encargar de traerlo a memoria y actualizar su indice
    }
    else
    {
        cout << "ERROR: Se intento acceder a un elemento inexistente." << endl;
    }
    archivo.close();
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

template <class T>
bool CacheManager<T>::write_file(string key, T obj)
{
    ofstream archivo(this->cacheFileName, ios::app);
    if (!archivo.is_open())
        return false;
    archivo << key << this->separadorKeyObj;
    archivo.write(reinterpret_cast<char *>(&obj), sizeof(T));
    archivo << endl;
    archivo.close();
    return true;
}

template <class T>
fstream CacheManager<T>::encontrarEnArchivo(string key)
{
    string linea;

    fstream archivo(this->cacheFileName, ios::in);

    for (int lineaNro = 0; getline(archivo, linea); lineaNro++)
    {
        if (lineaNro % 2 == 0 && linea == key) // En las lineas pares se guardan las keys
            break;
    }
    return archivo;
}

template <class T>
void CacheManager<T>::clear_file()
{
    ofstream archivo(this->cacheFileName, ios::trunc);
    archivo.close();
    return;
}