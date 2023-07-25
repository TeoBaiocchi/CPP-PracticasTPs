#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef char nodo;
typedef pair<pair<nodo, nodo>, int> arista;

typedef struct combina_encuentra{
    map<nodo, pair<nodo, nodo>> nombres;
    map<nodo, pair<nodo, int>> encabezados;
}conjunto_CE;

typedef priority_queue<arista, vector<arista>, MenorValor> arbol;

class MenorValor{
    public bool operator()(arista e1, arista e2){
        return e1.second > e2.second;
    }
};

class Grafo{
    private:
        vector<arista> aristas;
        vector<nodo> nodos;
        conjunto_CE CE;
        arbol grafo_ordenado;
        vector<arista> arbol_minimo;

    public:
        grafo(){};
        ~grafo(){};

        void agregar_nodo(const nodo&);
        void agregar_arista(const nodo&, const nodo&, const int&);

        vector<arista> get_aristas(){
            return this->aristas;
        }
        vector<nodo> get_nodos(){
            return this->nodos;
        }

        //void combina(const nodo&, const nodo&);
        //nodo encuentra(const nodo&);
        void kruskal ();

        //friend ostream& operator<< (ostream&, grafo);
};

void Grafo::agregar_nodo(const nodo& n){
    this->nodos.push_back(n);
}
void Grafo::agregar_arista(const arista& a){
    this->nodos.push_back(a);
}

int main(){
    cout << "hola" << endl;
    return 0;
}
