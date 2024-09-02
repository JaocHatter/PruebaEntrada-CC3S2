#include <bits/stdc++.h>
using namespace std;
#define forn(i,n) for(int i=0;i<n;i++)

struct arista {
    int idxDestino;
    int peso;
    arista *sgteArista;
};
typedef arista *parista;

struct vertice {
    int idx;
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
};
typedef vertice *pvertice;

vector<pvertice> g(1000);
vector<int> ord(1000, -1);

class grafo {
    private:
        pvertice pGrafo;
    public:
        grafo();
        ~grafo();
        void insertarVertice(int);
        void insertarArista(int, int, int);
        void imprimirGrafo();
        void dijkstra(int);
};

grafo::grafo() {
    pGrafo = NULL;
}

grafo::~grafo() {
    pvertice p, rp;
    parista r, ra;
    p = pGrafo;
    while (p != NULL) {
        r = p->adyacente;
        while (r != NULL) {
            ra = r;
            r = r->sgteArista;
            delete ra;
        }
        rp = p;
        p = p->sgteVertice;
        delete rp;
    }
}

void grafo::insertarVertice(int idx) {
    if (g[idx] != nullptr) {
        cout << "Identificador ya ocupado" << endl;
        return;
    }
    pvertice aux;
    aux = new vertice;
    aux->idx = idx;
    aux->adyacente = NULL;
    aux->sgteVertice = pGrafo;
    pGrafo = aux;
    g[idx] = aux;
}

void grafo::insertarArista(int idx, int idy, int peso) {
    pvertice p1, p2;
    parista a;
    p1 = g[idx];
    p2 = g[idy];
    if (p1 != NULL && p2 != NULL) {
        a = new arista;
        a->idxDestino = p2->idx;
        a->peso = peso;
        a->sgteArista = p1->adyacente;
        p1->adyacente = a;
    }
}

void grafo::dijkstra(int origen) {
    vector<int> dist(1000, INT_MAX);
    vector<bool> visitado(1000, false);
    dist[origen] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0,dist[origen]});
    int costo = 0;
    while(!pq.empty()){
        int v = pq.top().first;
        pq.pop();
        if(visitado[v]) continue;
        cout<<"La distancia minima al nodo: "<<v<<" es "<<dist[v]<<endl;
        visitado[v] = true;
        parista ady = g[v]->adyacente;
        while(ady != NULL){
            int w = ady->peso;
            if(!visitado[ady->idxDestino] && dist[ady->idxDestino] > dist[v] + w){
                dist[ady->idxDestino] = dist[v] + w;
                pq.push({ady->idxDestino,dist[ady->idxDestino]});
            }
            ady = ady->sgteArista;
        }
    }
}

int main() {
    grafo g;
    int n;
    cout<<"Nodo inicial: 0"<<endl;
    g.insertarVertice(0);
    cout<<"Cuantos Nodos mas deseas poner (sin incluir al nodo 0): ";
    cin>>n;
    forn(i,n){
        cout<<"Nodo "<<i+1<<" insertado"<<endl;
    }
    cout<<"======================"<<endl;
    cout<<"Cuantas aristas deseas agregar?: ";
    int n_aristas;
    cin>>n_aristas;
    cout<<"======================"<<endl;
    forn(i,n_aristas){
        int p,h,w;
        cout<<"Nodo padre: ";
        cin>>p;
        cout<<"Nodo hijo: ";
        cin>>h;
        cout<<"Peso de la arista: ";
        cin>>w;
        g.insertarArista(p, h, w);
        cout<<"======================"<<endl;
    }
    g.dijkstra(0);

    return 0;
}