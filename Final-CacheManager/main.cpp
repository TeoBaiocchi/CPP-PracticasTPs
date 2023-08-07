#include "cache.h"
#define LONGARRAY 255

using namespace std;

class Pelicula
{
    char nombre[LONGARRAY];
    int precio;
    int stock;

public:
    static const string class_name;  // Cada clase tiene un static llamado : class_name

    Pelicula(string _nombre, int _precio, int _stock){
        int i;
        for(i = 0; i < _nombre.length() && i < LONGARRAY ; i++){
            nombre[i] = _nombre[i];
        }
        nombre[i] = '\0';
        precio = _precio;
        stock = _stock;
    }

    friend ostream &operator<<(ostream &, Pelicula);

    void print(){
        cout << "Pelicula '" << nombre << "' - $" << precio << " - En Stock: " << stock << endl;
    }

    Pelicula(){};
    ~Pelicula(){};
};

const string Pelicula::class_name = "PeliculasClass";

ostream &operator<<(ostream &os, Pelicula pelicula)
{
    pelicula.print();
    return os;
}

void stockVideoClub();
void ejemploOriginal_ConStudent();

int main()
{
    stockVideoClub();
    //ejemploOriginal_ConStudent();
    return 0;
}

void stockVideoClub(){

    CacheManager<Pelicula> my_cache(5);

    cout << "1) generamos una cache de 5 espacios y guardamos 3 peliculas: " << endl;

    my_cache.insert("a", Pelicula("Asterix en Roma", 400, 3));
    my_cache.insert("b", Pelicula("Borat II", 100, 2));
    my_cache.insert("c", Pelicula("Charlie y La Fabrica de Chocolates", 700, 5));
    my_cache.show_cache();

    cout << endl << endl << "2) Agregamos una 4ta pelicula " << endl;
    my_cache.insert("d", Pelicula("Druk", 500, 3));
    my_cache.show_cache();

    cout << endl << endl << "3) Actualizamos precio y stock de la pelicula 'a' " << endl;
    my_cache.insert("a", Pelicula("Asterix En Roma", 500, 2));
    my_cache.show_cache();
    my_cache.mm.imprimirMemoria();
}



// -------------------------
// -------------------------
class Student
{
    int id;
    int value;
    const char *data;

public:
    static const string class_name;
    Student(int _key, int _value, const char *_data) : id(_key), value(_value), data(_data) {} // Cada clase tiene un static llamado : class_name
    friend ostream &operator<<(ostream &, Student);

    void print(){
        cout << "Student Object : " << id << " , " << value << " , " << data << endl;
    }

    Student(){};
    ~Student(){};
};

const string Student::class_name = "StudentClass";

ostream &operator<<(ostream &os, Student estudiante)
{
    cout << "Student Object : " << estudiante.id << " , " << estudiante.value << " , " << estudiante.data << endl;
    return os;
}

void ejemploOriginal_ConStudent(){
    CacheManager<Student> my_cache(3);
    my_cache.insert("0", Student(0, 22, "student1"));
    my_cache.insert("1", Student(1, 23, "student2"));
    my_cache.insert("2", Student(2, 25, "student3"));
    my_cache.insert("3", Student(3, 29, "student4"));
    Student return_obj = my_cache.get("0");
    my_cache.show_cache();


    cout << "---------------------- UPDATE -----------------------" << endl;
    my_cache.insert("2", Student(22, 222, "EZE"));
    my_cache.show_cache();

    cout << " <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<< <<<<<<<<<<<< <<<<" << endl;
    return_obj = my_cache.get("0"); // not in cache but in filesystem
    Student return_obj1 = my_cache.get("19");
    cout << " <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<< <<<<<<<<<<<< <<<<" << endl;
    my_cache.show_cache();

    my_cache.insert("2", Student(2, 25, "EZE"));
    my_cache.show_cache () ;

    my_cache.insert (" 9 ", Student(1, 5, "Nine"));
    my_cache.insert (" 9 ", Student (1, 5, "Nine"));
    my_cache.insert (" 9 ", Student (1, 5, "Nine"));
    my_cache.show_cache();
}

