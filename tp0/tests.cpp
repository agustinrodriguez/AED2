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

int main(void) {
	RUN_TEST(AnilloNuevoEsVacio);
    RUN_TEST(AnilloUnitarioAlEliminarQuedaVacio);
	RUN_TEST(AnilloUnitarioDaSiguiente);
	RUN_TEST(EliminarNodo);
    //RUN_TEST(MostrarAnilloVacio);

	return 0;
}

