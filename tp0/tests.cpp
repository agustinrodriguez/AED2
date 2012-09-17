#include "anillo.h"
#include "aed2_tests.h"
//#include "anillo.cpp"

template<typename T>
string to_s(const Anillo<T>* a) {
	ostringstream os;
	os << *a;
	return os.str();
}

void AnilloNuevoEsVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
	delete a;
}

void AnilloUnitarioAlEliminarQuedaVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
    a->agregar(42);
	ASSERT(!a->esVacio());
	ASSERT_EQ(a->tamanio(), 1);
    a->eliminar(42);
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
	delete a;
}

void AnilloUnitarioDaSiguiente() {
	Anillo<int>* a = new Anillo<int>();
    a->agregar(42);
    ASSERT(!a->esVacio());
    ASSERT_EQ(a->tamanio(), 1);
    ASSERT_EQ(a->siguiente(), 42);
	delete a;
}

void MostrarAnilloVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT_EQ(to_s(a), "[]");
	delete a;
}

void EliminarNodo(){
    Anillo<int>* a = new Anillo<int>();

    a->agregar(42);

    a->agregar(32);
    a->agregar(100);

    a->eliminar(42);
    ASSERT_EQ(to_s(a),"[100,32]");

    a->eliminar(100);
    ASSERT_EQ(to_s(a),"[32]");

    a->eliminar(32);
    ASSERT_EQ(to_s(a),"[]");

    delete a;
}

//AGREGADOS POR MI


void AnilloSacaNoSiguiente() {
        Anillo<int>* a = new Anillo<int>();
        a->agregar(42);
        a->agregar(20);
        a->eliminar(42);
        ASSERT_EQ(a->siguiente(), 20);
        ASSERT_EQ(a->tamanio(), 1);
        delete a;
}

void AnilloDeAnillo(){
        Anillo<Anillo<int> > a;
        a.agregar(Anillo<int>());
        Anillo<Anillo<int> > b(a);
}

//estos no dan
void UltimoEnAgregarEsElSiguiente() {
        Anillo<int>* a = new Anillo<int>();
        a->agregar(42);
        ASSERT_EQ(a->siguiente(), 42);
        a->agregar(20);
        ASSERT_EQ(a->siguiente(), 20);
        delete a;
}

void AnillosClonadoPreservaAnterior() {
        Anillo<int>* a = new Anillo<int>();
        a->agregar(42);
        a->agregar(20);
        a->siguiente();
        Anillo<int>* a2 = new Anillo<int>(*a);
        ASSERT_EQ(to_s(a), "[42,20*]");
        ASSERT_EQ(to_s(a2), "[42,20*]");
        delete a; delete a2;
}

void RetrocederUnaVezRepite() {
        Anillo<int>* a = new Anillo<int>();
        a->agregar(10);
        a->agregar(20);
        a->agregar(30);
        a->siguiente();
        ASSERT_EQ(to_s(a), "[20,10,30*]");
        a->retroceder();
        ASSERT_EQ(to_s(a), "[30*,20,10]");
        a->retroceder();
        ASSERT_EQ(to_s(a), "[10,30*,20]");
        delete a;
}

void MostrarAnillo() {
        Anillo<int>* a = new Anillo<int>();
        ASSERT_EQ(to_s(a), "[]");
        a->agregar(42);
        ASSERT_EQ(to_s(a), "[42]");
        a->agregar(2);
        ASSERT_EQ(to_s(a), "[2,42]");
        a->siguiente();
        ASSERT_EQ(to_s(a), "[42,2*]");
        a->siguiente();
        ASSERT_EQ(to_s(a), "[2,42*]");
        delete a;
}

void RetrocederAnillo(){
    Anillo<int>* a = new Anillo<int>();

	a->agregar(42);
	a->retroceder();
	ASSERT_EQ(to_s(a),"[42]");

	a->agregar(32);
    a->agregar(100);
    ASSERT_EQ(to_s(a),"[100,32,42]");
    a->siguiente();
    ASSERT_EQ(to_s(a),"[32,42,100*]");
    a->retroceder();
    ASSERT_EQ(to_s(a),"[100*,32,42]");
    delete a;
}


void ClonarConAnterior(){
    Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	a->agregar(32);
    a->agregar(100);
    a->siguiente();
    ASSERT_EQ(to_s(a),"[32,42,100*]");

    Anillo<int>* a2 = new Anillo<int>(*a);
    ASSERT_EQ(to_s(a2),"[32,42,100*]");
    delete a;
    delete a2;
}

void AnilloDeAnilloPuedenCrearseYUsarse(){
    Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	a->agregar(32);
	Anillo<int>* b = new Anillo<int>();
	b->agregar(100);
	Anillo<int>* c = new Anillo<int>();
    Anillo < Anillo <int> >* d = new Anillo < Anillo <int> >();
    d->agregar(*a);
    delete a;
    d->agregar(*b);
    delete b;
    d->agregar(*c);
    delete c;
    ASSERT_EQ(to_s(d),"[[],[100],[32,42]]");
    d->siguiente();
    ASSERT_EQ(to_s(d),"[[100],[32,42],[]*]");
    delete d;
}

/*void AnillosIguales(){
    Anillo<int>* a = new Anillo<int>();
    Anillo<int>* b = new Anillo<int>();
    ASSERT(*a==*b);
    a->agregar(1);
    a->agregar(2);
    a->agregar(3);

    b->agregar(1);
    b->agregar(2);
    b->agregar(3);
    ASSERT_EQ(to_s(a), to_s(b));
    ASSERT(*a==*b);
    delete a;
    delete b;
}*/

void AnilloPuedeRotarVariasVeces() {
    Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	a->agregar(32);
    a->agregar(100);
    ASSERT_EQ(to_s(a),"[100,32,42]");
    a->siguiente();
    ASSERT_EQ(to_s(a),"[32,42,100*]");
    a->siguiente();
    ASSERT_EQ(to_s(a),"[42,100,32*]");
    a->siguiente();
    ASSERT_EQ(to_s(a),"[100,32,42*]");
    delete a;
}



int main(void) {
	RUN_TEST(AnilloNuevoEsVacio);
    RUN_TEST(AnilloUnitarioAlEliminarQuedaVacio);
	RUN_TEST(AnilloUnitarioDaSiguiente);
	RUN_TEST(EliminarNodo);
    RUN_TEST(MostrarAnilloVacio);
    RUN_TEST(UltimoEnAgregarEsElSiguiente);
    RUN_TEST(AnilloSacaNoSiguiente);
    RUN_TEST(MostrarAnillo);
    RUN_TEST(AnillosClonadoPreservaAnterior);
    RUN_TEST(RetrocederUnaVezRepite);
    RUN_TEST(AnilloDeAnillo);
    RUN_TEST(RetrocederAnillo);
    RUN_TEST(ClonarConAnterior);
//    RUN_TEST(AnillosIguales);
    RUN_TEST(AnilloDeAnilloPuedenCrearseYUsarse);
    RUN_TEST(AnilloPuedeRotarVariasVeces);
	return 0;
}

