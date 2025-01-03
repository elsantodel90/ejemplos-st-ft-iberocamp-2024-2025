#include <iostream>

using namespace std;

const int MAXN = 1000000;

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

// ft[0] no se usa (le dejamos el neutro)
// Para i > 0,
// ft[i] guarda la operacion en el rango [i - lastBit(i) , i)
Data ft[MAXN];

int lastBit(int x)
{
    return x & (-x);
}

// Operacion en [0,i)
Data getPrefix(int i)
{
    Data ret;
    for (; i > 0; i -= lastBit(i))
        ret.acum(ft[i]);
    return ret;
}

// Operacion en [0,i)
void acum(int i, const Data &value)
{
    // i+1 es el mas chico en contener al i
    // Y por eso el primero a modificar
    for (i++; i < MAXN; i += lastBit(i))
        ft[i].acum(value);
}

int main()
{
    acum(3,Data(7));
    cout << getPrefix(10).s << endl;
    cout << getPrefix(11).s << endl;
    acum(3,Data(-2));
    acum(10,Data(-1));
    cout << getPrefix(10).s << endl;
    cout << getPrefix(11).s << endl;
    return 0;
}
