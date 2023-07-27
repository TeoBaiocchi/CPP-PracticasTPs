//NT: NT = Nota Teo

#include "cache.h"

using namespace std; //NT: Averiguar por que esto es mala práctica.
class Student{
    int id;
    int value;
    const char * data;

    public:
        static const string class_name; //Cada clase tiene un static llamado : class_name
        //NT: Ok, pero averiguar por qué

        Student(int _key, int _value, const char * _data ):id(_key), value( _value), data(_data){}
        //NT: Puede ser obvio, pero el uso de ":" es una forma de "abreviar" la declaración del constructor
        //Indica que dados esos parametros, correspodnen de esa manera a los valores puestos de la clase student.

    void print(){
        cout << "Student Object : " << id << " , " << value << " , " << data << endl;
    };

    ~Student(){};
};

const string Student::class_name = "StudentClass";

int main(){

    CacheManager<Student> my_cache(3);
    //NT: Igual que en cualquier colección de un lenguaje de OOP, se indica la estructura y el tipo que recibe
    //Recordar que en el caso particular de este ejercicio toma como parametro el tamaño.
    Student estudiante1 = Student(0, 22, "student1");
    my_cache.insert("0", estudiante1);
    my_cache.insert("1", Student(1, 23, "student2"));
    my_cache.insert("2", Student(2, 25, "student3"));
    my_cache.insert("3", Student(3, 29, "student4"));
//    my_cache.show_cache();

    cout << "---------------------- UPDATE -----------------------" << endl;
    my_cache.insert(" 2 ", Student(22, 222, " EZE "));
//    my_cache.show_cache();

    cout << " <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<< <<<<<<<<<<<< <<<<" << endl;
//    Student return_obj = my_cache.get(" 0 "); // not in cache but in filesystem
    //Al tener 4 valores, uno debe ser reemplazado por tener el limite de 3 en cache... y "0" es el LRU.
    cout << " <<<<<< <<<<<<<<<<<< <<<<<<<<<<<< <<<<<<<<<<< <<<<<<<<<<<< <<<<" << endl;

    my_cache.insert("2", Student(2, 25, "EZE"));
//    my_cache.show_cache () ;

//    my_cache.insert (" 9 ", Student(1, 5, "Nine"));
//    my_cache.insert (" 9 ", Student (1, 5, "Nine"));
//    my_cache.insert (" 9 ", Student (1, 5, "Nine"));
//    my_cache.show_cache();

return 0;
}
