#include "../DiccTrie.h"
#include <cstdlib>
#include "../aed2.h"
using namespace std;

void testTrieVacio(ostream&){
    DiccTrie<int> d;
    String clave1 = "test";
    String clave2 = "cualquiera";
    NEGAR(d.Def(clave1));
    NEGAR(d.Def(clave2));
}

void testDefinido(ostream&) {
    DiccTrie<int> d;
    String clave1 = "test";
    String clave2 = "cualquiera";
    String clave3 = "noesta";
    int sig1 = 1;
    int sig2 = 2;
    d.Definir(clave1, sig1);
    d.Definir(clave2, sig2);
    AFIRMAR(d.Def(clave1));
    AFIRMAR(d.Def(clave2));
    NEGAR(d.Def(clave3));
}

void testObtener(ostream&) {
    DiccTrie<int> d;
    String clave1 = "test";
    String clave2 = "cualquiera";
    String clave3 = "noesta";
    int sig1 = 1;
    int sig2 = 2;
    int sig3 = 3;
    d.Definir(clave1, sig1);
    d.Definir(clave2, sig2);
    d.Definir(clave3, sig3);
    ASEGURAR(d.Obtener(clave1),sig1);
    ASEGURAR(d.Obtener(clave2),sig2);
    ASEGURAR(d.Obtener(clave3),sig3);
    sig3 = 4;
    d.Definir(clave3,sig3);
    ASEGURAR(d.Obtener(clave3),"4");
}


//int main(int argc, char** argv) {
int main(int, char**) {
    cout << endl;
    Tester& tester = *Tester::Instance();
    tester.NuevoSet("DiccTrie",0);
    tester.UsarSet("DiccTrie");
    tester.Declarar("vacio",&testTrieVacio,0);
    tester.Declarar("definido",&testDefinido,0);
    tester.Declarar("obtener",&testObtener,0);
    tester.EjecutarTodos();

    return 0;
}

