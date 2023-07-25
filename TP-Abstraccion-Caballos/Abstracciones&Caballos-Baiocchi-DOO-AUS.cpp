#include <iostream>
#include <vector>

using namespace std;

class Animal {

    private:
        int pesoEnKg;
        int cantidadPatas;
        bool acuatico;
        bool terrestre;
        string especie;
        string dieta;

    public:
        virtual void valoresPorDefecto(){
        pesoEnKg = 0;
        acuatico = false;
        terrestre = false;
        cantidadPatas = 0;
        especie = "Indefinida";
        dieta = "Indefinida";
        }

        virtual string dejaHuellas();

        // ---------- Getters y setters -----------
        void setDieta(string n){
            this->dieta = n;
        }
        string getDieta(){
            return dieta;
        }
        void setEspecie(string n){
            this->especie = n;
        }
        string getEspecie(){
            return especie;
        }
        void setTerrestre(bool n){
            this->terrestre = n;
        }
        bool isTerrestre(){
            return terrestre;
        }
        void setAcuatico(bool n){
            this->acuatico = n;
        }
        bool isAcuatico(){
            return acuatico;
        }
        void setPeso(int n){
            this->pesoEnKg = n;
        }
        int getPeso(){
            return pesoEnKg;
        }
        void setCantidadPatas(int n){
            this->cantidadPatas = n;
        }
        int getCantidadPatas(){
            return cantidadPatas;
        }
};

string Animal::dejaHuellas(){
    string mensaje = "";
        if(terrestre){
            if(cantidadPatas == 0){
                mensaje = "Debido a su falta de patas, deja un rastro en forma de camino más que una huella.";
            } else {
                mensaje = "debido a sus " + std::to_string(cantidadPatas) + " patas y su peso de " + std::to_string(pesoEnKg) + ", deja huellas ";
                if(pesoEnKg < 15){
                    mensaje = mensaje + "casi imperceptibles.";
                }
                if(pesoEnKg > 15 && pesoEnKg < 60){
                    mensaje = mensaje + "visibles para el ojo atento.";
                }
                if(pesoEnKg > 60){
                    mensaje = mensaje + "profundas y claras a la vista.";
                }
            }
        } else {
            mensaje = "Debido a que no pisa tierra, no deja huellas.";
        }
    return mensaje;
}

class Caballo : public Animal{
    private:
        string nombre;
    public:
        //El constructor instancia los valores por defecto de cualquier animal y luego especifica los que necesita
        Caballo(){
            valoresPorDefecto();
            setNombre("Sin Nombre");
            setEspecie("Caballo");
            setCantidadPatas(4);
            setTerrestre(true);
            setPeso(800); //peso promedio de un equino
            setDieta("Herviboro");
        }

        // getters y setters
        void setNombre(string n){
            this->nombre = n;
        }

        string getNombre(){
            return nombre;
        }
};

int main(){

    Caballo caballoSalvaje = Caballo();

    Caballo brunello = Caballo();
    brunello.setNombre("Brunello");

    Caballo viernes = Caballo();
    viernes.setNombre("Viernes");


    cout << brunello.getNombre() << ", como cualquier equino, "  << brunello.dejaHuellas() << endl;
    cout << "Sin embargo, sin verlo en carne propia es imposible distinguir sus huellas de las de cualquier caballo Sin Nombre." << endl;
    cout << endl << endl;
    cout << "Ejemplo 2: " << endl << "Un vaquero llega a un pueblo un lunes, se queda dos dias y vuelve en Viernes." << endl
    << "Como lo hizo?" << endl << "El caballo se llamaba " << viernes.getNombre() << endl;
    return 0;
}

