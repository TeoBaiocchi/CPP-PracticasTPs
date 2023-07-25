#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include<utility>

using namespace std;

typedef char nodo;

typedef pair<pair<nodo, nodo>, int> arista;

typedef struct combina_encuentra{
    map<char, pair<nodo, nodo>> nombres;
    map<char, pair<int, nodo>> encabezados;
}conjunto_CE;

class MenorValor{
    public:
        bool operator()(arista e1, arista e2){
            return e1.second > e2.second;
        }
};

typedef priority_queue<arista, vector<arista>, MenorValor> arbol;

class Grafo{

    private:
        vector<arista> aristas;
        vector<nodo> nodos;
        conjunto_CE CE;
        arbol grafo_ordenado;
        vector<arista> arbol_minimo;
        void inicial(const nodo&, const nodo&);

    public:
        grafo(){};
        void agregar_nodo(const nodo&);
        void agregar_arista(const nodo&, const nodo&, const int&);
        bool nodo_en_grafo(const nodo);
        void combina(const nodo&, const nodo&);
        nodo encuentra(const nodo&);
        void inserta(const arista&);
        void imprimir_arbolMinimo();
        void kruskal();
        friend ostream& operator<< (ostream&, Grafo);

        vector<arista> get_aristas(){
            return this->aristas;
        }
        vector<nodo> get_nodos(){
            return this->nodos;
        }
};

ostream& operator <<(ostream& os, Grafo grafito){
	os << "El Grafo consta de: \n";
	for(auto x: grafito.get_aristas())
		os << x.first.first << " - " << x.first.second << ": costo = " << x.second << endl;
	return os;
}

void Grafo::imprimir_arbolMinimo(){
    cout << "El arbol minimo consta de: " << endl;
    for(auto ar : arbol_minimo){
        cout << "[(" << ar.first.first  <<  ", " << ar.first.second << "):" << ar.second << "]" << endl;
    }
}


// Funciones de construccion de grafo ------------------------------------------------------------------

void Grafo::agregar_arista(const nodo& n1, const nodo& n2, const int& peso){
    if(nodo_en_grafo(n1) && nodo_en_grafo(n2)){
        arista ar;
        ar.first = make_pair(n1, n2);
        ar.second = peso;
        this->aristas.push_back(ar);
        cout << "Se agrego con exito la arista [(" << ar.first.first  <<  ", " << ar.first.second << "):" << ar.second << "]" << endl;
    } else {
    cout << "Se intento agregar una arista [(" << n1  <<  ", " << n2 << "):" << peso << "] con nodos que no pertenecen al grafo." << endl;
    }
}

void Grafo::agregar_nodo(const nodo& n){
    if(!nodo_en_grafo(n)){
        this->nodos.push_back(n);
        cout << "Se agrego con exito el nodo '" << n << "'" << endl;
    } else {
        cout << "Se intento agregar el nodo '" << n << "' que ya existe en el grafo." << endl;
    }

}

bool Grafo::nodo_en_grafo(const nodo n){
    for(nodo naux : this->get_nodos()){
        if(naux == n){
            return true;
        }
    }
    return false;
}


// Funciones Combina encuentra -----------------------------------------

void Grafo::inicial(const nodo& n, const char& indice){
     CE.nombres.insert(make_pair(indice, make_pair(n, 0)));
     CE.encabezados.insert(make_pair(indice, make_pair(1, n)));
}

char Grafo::encuentra (const nodo& n){
    return CE.nombres[n].first;
}

// nota: en nombres     es indice(nombre, siguiente)
//       en encabezados es indice(cuenta, primer elemento)
void Grafo::combina(const nodo& N1, const nodo& N2){
  nodo elem;
  if (CE.encabezados[N1].first > CE.encabezados[N2].first) {
    elem = CE.encabezados[N2].second;
    do {
      CE.nombres[elem].first = N1;
      elem = CE.nombres[elem].second;
    } while (CE.nombres[elem].second != '\0');
  } else { // Al reves...
    elem = CE.encabezados[N2].second;
    do {
      CE.nombres[elem].first = N2;
      elem = CE.nombres[elem].second;
    } while (CE.nombres[elem].second != '\0');
  }
}




// Kruskal ------------------------------------------------------------

void Grafo::inserta(const arista& ar){
    grafo_ordenado.push(ar);
}

void Grafo::kruskal(){

    for(arista ar: aristas){        //genero la priority queque
        inserta(ar);
    }
    for(nodo n: nodos){             //genero las componentes individuales
        inicial(n, n);
    }
    int componentes = nodos.size(); //inicializo el contador
    nodo comp1, comp2;
    arista arMenor;

    while(componentes > 1){
        arMenor = grafo_ordenado.top();           // obtengo la arista menor
        grafo_ordenado.pop();                     // y la elimino de la queque
        comp1 = encuentra(arMenor.first.first);
        comp2 = encuentra(arMenor.first.second);  // obtengo las componentes a las que pertencen los vertices de la arista
        if (comp1 != comp2){                      //Si son diferentes...
            combina(comp1, comp2);                // aplicamos la operacion combina
            componentes = componentes -1;         // restamos al contador
            arbol_minimo.push_back(arMenor);      // y sumamos al arbol minimo
        }
    }
}

// Ejemplo ------------------------------------------------

int main(){
    cout << "-- Kruskal --" << endl << endl;


    Grafo grafito = Grafo();
    cout << "Ejemplo: 'grafito' es creado, tomando el ejemplo del apunte combina_encuentra" << endl;

    grafito.agregar_nodo('a');
    grafito.agregar_nodo('b');
    grafito.agregar_nodo('c');
    grafito.agregar_nodo('d');
    grafito.agregar_nodo('e');
    grafito.agregar_nodo('f');

    grafito.agregar_arista('a', 'b', 6);//1, 2, 6
    grafito.agregar_arista('a', 'c', 1); //1, 3, 1
    grafito.agregar_arista('d', 'f', 2); //4, 6, 2
    grafito.agregar_arista('a', 'd', 5); //1,4, 5
    grafito.agregar_arista('b', 'e', 3); //2, 5, 3
    grafito.agregar_arista('c', 'f', 4); //3,6, 4
	grafito.agregar_arista('b', 'c', 5); //2,3, 5
	grafito.agregar_arista('c', 'd', 5);//3, 4, 5
	grafito.agregar_arista('c', 'e', 6);//3, 5, 6
	grafito.agregar_arista('e', 'f', 6);//5, 6, 6

    grafito.kruskal();
    cout << grafito;
    grafito.imprimir_arbolMinimo();

    return 0;
}
