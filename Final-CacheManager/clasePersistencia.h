#include <string>

using namespace std;

template <class T>
class ClaseDePersistencia
{
public:
    string key;
    T dato;

    ClaseDePersistencia();
     ClaseDePersistencia(string, T);
    ~ClaseDePersistencia();
};

template <class T>
ClaseDePersistencia<T>::ClaseDePersistencia(string key, T generico)
{
    this->key = key;
    this->dato = generico;
}

template <class T>
ClaseDePersistencia<T>::ClaseDePersistencia(){}

template <class T>
ClaseDePersistencia<T>::~ClaseDePersistencia(){}


