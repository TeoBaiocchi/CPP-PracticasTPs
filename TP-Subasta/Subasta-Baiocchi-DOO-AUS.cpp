#include <iostream>
#include <vector>

using namespace std;

/*
Consigna:
La idea es que una subasta consiste en un conjunto de items ofertados para la venta.
Estos items son llamados lotes. Las Personas ingresan ofertas para los lotes
y la mas elevada es la que se registra en el Lote. Ni la Persona ni la Oferta inicia la actividad en la subasta.
La persona solo posee un nombre. Y la oferta guarda el monto y el ofertante.
El lote, tiene un numero y un nombre, ademas se guarda la oferta mas grande.
La subasta guarda la coleccion de lotes y la cantidad de los mismos.
Debe realizar y enbtregar el diagrama de clases del sistema y la codificación del mismo.
*/


//"La persona solo posee un nombre"
class Persona {

    private:
        string nombre;

    public:
        Persona(){nombre = "Anonimo";}         //Constructor vacio
        Persona(string n){nombre = n;}        // Constructor con parametros

         //Getter y setter
        void setNombre(string n){
            this->nombre = n;
        }
        string getNombre(){
            return nombre;
        }
};



// "la oferta guarda el monto y el ofertante."
class Oferta{

    private:
        Persona ofertante;
        int monto;

    public:
        //Los constructores en este caso permiten instanciar una oferta vacia por defecto, o completa.
        Oferta(){
            ofertante = Persona();
            monto = 0;
        }

        Oferta(Persona o, int i){
            this->ofertante = o;
            this->monto = i;
        }

        //Getters y setters:
        void setPersona(Persona o){
            this->ofertante = o;
        }

        void setMonto(int i){
            this->monto = i;
        }

        Persona getOfertante(){
            return this->ofertante;
        }

        int getMonto(){
            return this->monto;
        }
};



//"El lote, tiene un numero y un nombre, ademas se guarda la oferta mas grande."
class Lote{

    private:
        int numLote;
        string denominacion;
        Oferta ofertaVigente;

    public:
        //Los constructores permiten un lote por defecto, un lote con propiedades pero sin oferta, y un lote completo
        Lote(){
            numLote = 0; //En un programa real, este valor por defecto lo usaria para detectar un lote sin definir
            denominacion = "-";
            ofertaVigente = Oferta();
        }

        Lote(int n, string s){
            numLote = n;
            denominacion = s;
            ofertaVigente = Oferta();
        }

        Lote(int n, string s, Oferta o){
            numLote = n;
            denominacion = s;
            ofertaVigente = o;
        }

        //Impresion de lote
        void imprimirLote();

        //getters y setters
        void setNumLote(int n){
            numLote = n;
        }

        int getNumLote(){
            return numLote;
        }

        void setDenominacion(string d){
            denominacion = d;
        }

        string getDenominacion(){
            return denominacion;
        }

        void setOfertaVigente(Oferta o){
            ofertaVigente = o;
        }

        Oferta getOfertaVigente(){
            return ofertaVigente;
        }
};

void Lote::imprimirLote(){
    cout << "Datos de Lote " << this->numLote << ": " << this->denominacion << endl
    << "Oferta Vigente: " << this->ofertaVigente.getOfertante().getNombre() << " | $" << this->ofertaVigente.getMonto() << endl;
}



//"La subasta guarda la coleccion de lotes y la cantidad de los mismos."
class Subasta{

    private:
        vector<Lote> lotesSubastados;

    public:
        Subasta(){}

        int getCantidadDeLotes(){
            return lotesSubastados.size();
        }

        void imprimirTodosLotes();
        Lote getLoteX(int i);
        void agregarLote(Lote l);

        //Getter y setter
        void setLotesSubastados(vector<Lote> v){
            lotesSubastados = v;
        }

        vector<Lote> getLotesSubastados(){
            return lotesSubastados;
        }
};

void Subasta::imprimirTodosLotes(){
    int tamanio = this->lotesSubastados.size();
    cout << "--> La Subasta esta comprendida por los siguientes (" << tamanio << ") Lotes <-- " << endl;
    for(int i; i < tamanio; i++){
        cout << endl;
        this->lotesSubastados[i].imprimirLote();
    }
    cout << endl << "------------" << endl;
}

void Subasta::agregarLote(Lote l){
    this->lotesSubastados.push_back(l);
}

Lote Subasta::getLoteX(int i){
    return this->lotesSubastados[i];
}


int main(){

    cout << "Para ejemplificar, el programa automaticamente crea 4 personas, ofertas, y lotes con valores pre-definidos." <<
    endl << "Estos valores se crean jugando un poco con la flexibilidad de los constructores para testearlos." <<
    endl << endl << "Una vez creados, se asignan a una subasta tambien de ejemplo, y desde ella son impresos con el metodo"<<
    endl << "dado por la propia subasta para imprimir todos sus lotes como se ve a continuacion: " << endl
    << endl << endl << endl;

    Persona persona1 = Persona("Arturo");
    Persona persona2 = Persona("Maria");
    Persona persona3 = Persona("Harry");
    Persona persona4 = Persona("Kim");

    Oferta oferta1 = Oferta(persona1, 50);
    Oferta oferta2 = Oferta(persona2, 100);
    Oferta oferta3 = Oferta(persona3, 1);
    Oferta oferta4 = Oferta(persona4, 300);

    Lote loteVacio = Lote();

    Lote lote1 = Lote();
    lote1.setDenominacion("Cuadro Arte Moderno");
    lote1.setNumLote(1);
    lote1.setOfertaVigente(oferta1);

    Lote lote2 = Lote(2, "Guitarra Fender Vintage 1966");
    lote2.setOfertaVigente(oferta2);

    Lote lote3 = Lote(3, "Lote Libros Antiguos", oferta3);

    Lote lote4 = Lote(4, "Bajo Hofner" , oferta4);

    Subasta subasta = Subasta();

    subasta.agregarLote(lote1);
    subasta.agregarLote(lote2);
    subasta.agregarLote(lote3);
    subasta.agregarLote(lote4);
    subasta.agregarLote(loteVacio);

    subasta.imprimirTodosLotes();

    return 0;
}
