/*#include "cache.h"

template <class T>
void CacheManager<T>::actualizarEnMemoria(string key, T obj)
{
    T objAux;
    vector<string> indices;
    vector<T> objetos;
    string linea;

    // Copio el contenido del archivo
    ifstream archivo((this->cacheFileName), ios::in | ios::binary);
    cout << "LECTURA DE ARCHIVO: " << endl;
    for (int lineaNro = 0; getline(archivo, linea); lineaNro++)
    {
        if (lineaNro % 2 == 0)
        {
            indices.push_back(linea);
        }
        else
        {
            archivo.read(reinterpret_cast<char *const>(&objAux), sizeof(T));
            objetos.push_back(objAux);
        }
    }
    archivo.close();

    // Limpio el archivo
    remove(this->cacheFileName.c_str());

    // Vuelvo a armar el archivo, omitiendo el indice desactualizado
    for (int i = 0; i < indices.size(); i++)
    {
        cout << "OBJETO : " << indices[i] << " " << objetos[i];
        if (indices[i] != key)
        {
            cout << " (VALIDADO)" << endl;
            write_file(indices[i], objetos[i], this->cacheFileName);
        }
    }

    // Finalmente agrego el valor actualizado
    write_file(key, obj, this->cacheFileName);
}

template <class T>
bool CacheManager<T>::existeKeyEnMemoria(string key)
{

    string linea;
    ifstream archivo(this->cacheFileName, ios::in | ios::binary);

    for (int lineaNro = 0; getline(archivo, linea); lineaNro++)
    {
        if (lineaNro % 2 == 0 && linea == key)
        { // En las lineas pares se guardan las keys
            return true;
        }
    }
    return false;
}

template <class T>
ifstream CacheManager<T>::encontrarEnMemoria(string key)
{
    string linea;
    ifstream archivo(this->cacheFileName, ios::in | ios::binary);

    for (int lineaNro = 0; getline(archivo, linea); lineaNro++)
    {
        if (lineaNro % 2 == 0 && linea == key)
        { // En las lineas pares se guardan las keys
            getline(archivo, linea);
            break;
        }
    }
    return archivo;
}

template <class T>
bool CacheManager<T>::write_file(string key, T obj, string nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::out | ios::binary);
    // archivo << key << this->separadorKeyObj;
    archivo.write(reinterpret_cast<char *const>(&obj), sizeof(T));
    archivo << endl;
    archivo.close();
    return true;
}
*/