#include "cache.h"

using namespace std;

class Pelicula
{
    string id;
    string nombre;
    int precio;
    int stock;

public:
    static const string class_name;                                                            // Cada clase tiene un static llamado : class_name
    Pelicula(string _id, string _nombre, int _precio, int _stock) : id(_id), nombre(_nombre), precio(_precio), stock(_stock){}
    friend ostream &operator<<(ostream &, Pelicula);
    Pelicula(){};
    ~Pelicula(){};
};

const string Pelicula::class_name = "PeliculasClass";

ostream &operator<<(ostream &os, Pelicula pelicula)
{
    cout << "Pelicula (" << pelicula.id << "): '" << pelicula.nombre << "' - $" << pelicula.precio << " - En Stock: " << pelicula.stock << endl;
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

    cout << "1) generamos una cache de 5 espacios y guardamos 3 peliculas: " << endl;

    CacheManager<Pelicula> my_cache(5);
    my_cache.insert("a", Pelicula("a", "Asterix En Roma", 400, 3));
    my_cache.insert("b", Pelicula("b", "Borat II", 100, 2));
    my_cache.insert("c", Pelicula("c", "Charlie y La Fabrica de Chocolates", 700, 5));
    my_cache.show_cache();

    cout << endl << endl << "2) Agregamos una 4ta pelicula " << endl;
    my_cache.insert("d", Pelicula("d", "Druk", 500, 3));
    my_cache.show_cache();

    cout << endl << endl << "3) Actualizamos precio y stock de la pelicula 'a' " << endl;
    my_cache.insert("a", Pelicula("a", "Asterix En Roma", 500, 2));
    my_cache.show_cache();
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

