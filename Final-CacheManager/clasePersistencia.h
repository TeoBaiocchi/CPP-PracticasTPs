#include <string>
#define LONGKEY 16
using namespace std;

template <class T>
class ClaseDePersistencia
{
public:
    char key[LONGKEY];
    T dato;

    ClaseDePersistencia();
    ClaseDePersistencia(string, T);
    ~ClaseDePersistencia();
};

template <class T>
ClaseDePersistencia<T>::ClaseDePersistencia(string key, T generico)
{
    int i;
    for (i = 0; (size_t)i < key.length() && i < LONGKEY; i++)
    {
        this->key[i] = key[i];
    }
    this->key[i] = '\0';
    this->dato = generico;
}

template <class T>
ClaseDePersistencia<T>::ClaseDePersistencia() {}

template <class T>
ClaseDePersistencia<T>::~ClaseDePersistencia() {}
