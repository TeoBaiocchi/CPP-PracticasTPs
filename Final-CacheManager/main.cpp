#include "cache.h"

using namespace std;
class Student
{
    int id;
    int value;
    const char *data;

public:
    static const string class_name;                                                            // Cada clase tiene un static llamado : class_name
    Student(int _key, int _value, const char *_data) : id(_key), value(_value), data(_data) {} // NT: Puede ser obvio, pero el uso de ":" es una forma de "abreviar" la declaraci�n del constructor. Indica que dados esos parametros, correspodnen de esa manera a los valores puestos de la clase student.
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




int main()
{

    CacheManager<Student> my_cache(3);
    my_cache.insert("0", Student(0, 22, "student1"));
    my_cache.insert("1", Student(1, 23, "student2"));
    my_cache.insert("2", Student(2, 25, "student3"));
    my_cache.insert("3", Student(3, 29, "student4"));
    Student return_obj = my_cache.get("0");
    my_cache.show_cache();
    // 1 2 y 3, cuando inserta a 3 borra a 0

    cout << "---------------------- UPDATE -----------------------" << endl;
    my_cache.insert("2", Student(22, 222, "EZE"));
    my_cache.show_cache();
    // 2 tiene que cambiar a EZE

    cout << " <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<< <<<<<<<<<<<< <<<<" << endl;
    return_obj = my_cache.get("0"); // not in cache but in filesystem
    Student return_obj1 = my_cache.get("19");
    cout << " <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<< <<<<<<<<<<<< <<<<" << endl;
    my_cache.show_cache();

    //    my_cache.insert("2", Student(2, 25, "EZE"));
    //    my_cache.show_cache () ;

    //    my_cache.insert (" 9 ", Student(1, 5, "Nine"));
    //    my_cache.insert (" 9 ", Student (1, 5, "Nine"));
    //    my_cache.insert (" 9 ", Student (1, 5, "Nine"));
    //    my_cache.show_cache();

    return 0;
}

