#include <iostream>

using namespace std;

const int MAXN = 1<<20;

struct Data
{
    int s;
    Data () { s = 0; } // NEUTRO
    explicit Data (int x) { s = x; }
    void acum(const Data &o)
    {
        s += o.s;
    }
};

int leftChild(int x) { return 2*x; }
int rightChild(int x) { return 2*x+1; }
int parent(int x) { return x/2; }


// Usamos que MAXN es potencia de 2
// st[MAXN + i] es la hoja i-esima
// st[1] es la raiz
// st[0] no se usa (pero seria "un padre de la raiz y de si mismo")
Data st[2*MAXN];
int queryA, queryB; // Auxiliares para la query recursiva
Data queryUpdate; // si es range-update

// Operacion en [0,i)
Data iterateRange(int node,int nodeA, int nodeB)
{
    if (queryA <= nodeA && nodeB <= queryB)
    {
        // Este nodo es uno de los sub-rangos clave!
        // Si es un range-update, aca modificariamos st[node]
        // usando queryUpdate
        return st[node];
    }
    if (nodeB <= queryA || queryB <= nodeA)
    {
        // Nodo totalmente disjunto con la query
        return Data();
    }
    // Ni todo ni nada: que se encarguen los hijos
    int mid = (nodeA+nodeB)/2;
    Data ret;
    ret.acum(iterateRange(leftChild(node), nodeA, mid));
    ret.acum(iterateRange(rightChild(node), mid, nodeB));
    return ret;
}

// void iterateRange(int a,int b, const Data& upd) si es range update
Data iterateRange(int a,int b)
{
    queryA = a;
    queryB = b;
    // queryUpdate = upd; si es range update
    return iterateRange(1,0,MAXN);
}

//Data iteratePoint(int i) si es point query
void iteratePoint(int i, const Data& upd)
{
    int node = MAXN + i;
    st[node].acum(upd);
    //Data ret; si es point query
    while (node >= 1)
    {
        //ret.acum(st[node]); si es point query
        node = parent(node);
        st[node] = st[leftChild(node)];
        st[node].acum(st[rightChild(node)]);
    }
    // return ret; si es point query
}


int main()
{
    iteratePoint(3,Data(7));
    cout << iterateRange(0,10).s << endl;
    cout << iterateRange(0,11).s << endl;
    iteratePoint(3,Data(-2));
    iteratePoint(10,Data(-1));
    cout << iterateRange(0,10).s << endl;
    cout << iterateRange(0,11).s << endl;
    return 0;
}
