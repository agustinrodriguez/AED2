#include "anillo.h"
#include "aed2_tests.h"

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

void AnilloPuedeRotarVariasVeces() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->agregar(3);
	a->siguiente();
	a->siguiente();
	a->siguiente();
	a->siguiente();
	a->siguiente();
	a->siguiente();
	a->siguiente();
	a->siguiente();
	ASSERT_EQ(to_s(a), "[1, 3, 2]");
	delete a;
}

// borrar
void AnilloUnitarioCicla() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	ASSERT_EQ(a->siguiente(), 42);
	ASSERT_EQ(a->siguiente(), 42);
	ASSERT_EQ(a->siguiente(), 42);
	ASSERT_EQ(a->siguiente(), 42);
	delete a;
}

void UltimoEnAgregarEsElActual() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	ASSERT_EQ(a->actual(), 42);
	a->agregar(20);
	ASSERT_EQ(a->actual(), 20);
	a->agregar(10);
	ASSERT_EQ(a->actual(), 10);
	delete a;
}

void MasNuevosQuedanPrimeros() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	a->agregar(20);
	a->agregar(10);
	ASSERT_EQ(a->actual(), 10);
	ASSERT_EQ(a->siguiente(), 20);
	ASSERT_EQ(a->siguiente(), 42);
	delete a;
}

void AnilloConDosCicla() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	a->agregar(20);
	ASSERT_EQ(a->siguiente(), 42);
	ASSERT_EQ(a->siguiente(), 20);
	ASSERT_EQ(a->siguiente(), 42);
	ASSERT_EQ(a->siguiente(), 20);
	delete a;
}

void AnilloSacaNoSiguiente() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	a->agregar(20);
	a->eliminar(42);
	ASSERT_EQ(a->siguiente(), 20);
	ASSERT_EQ(a->tamanio(), 1);
	delete a;
}

void MostrarAnillo() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT_EQ(to_s(a), "[]");
	a->agregar(42);
	ASSERT_EQ(to_s(a), "[42]");
	a->agregar(2);
	ASSERT_EQ(to_s(a), "[2, 42]");
	a->siguiente();
	ASSERT_EQ(to_s(a), "[42, 2]");
	a->marcar();
	a->siguiente();
	ASSERT_EQ(to_s(a), "[2, 42*]");
	a->siguiente();
	ASSERT_EQ(to_s(a), "[42*, 2]");
	delete a;
}

void MostrarAnillo2()
{
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->agregar(3);
	ASSERT_EQ(to_s(a), "[3, 2, 1]");
	delete a;
}

void AnillosClonadoPreservaMarcado() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(42);
	a->agregar(20);
	a->marcar();
	a->siguiente();
	Anillo<int>* a2 = new Anillo<int>(*a);
	ASSERT_EQ(to_s(a), "[42, 20*]");
	ASSERT_EQ(to_s(a2), "[42, 20*]");
	delete a;
	delete a2;
}

void PuedeEliminarMarcado() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(10);
	a->agregar(20);
	a->agregar(30);
	a->marcar();
	a->siguiente();
	ASSERT_EQ(to_s(a), "[20, 10, 30*]");
	ASSERT(a->hayMarcado());
	a->eliminar(30);
	ASSERT_EQ(to_s(a), "[20, 10]");
	ASSERT(!a->hayMarcado());
	delete a;
}

void PuedeEliminarSiguiente() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(10);
	a->agregar(20);
	a->agregar(30);
	ASSERT_EQ(to_s(a), "[30, 20, 10]");
	a->eliminar(30);
	ASSERT_EQ(to_s(a), "[20, 10]");
	delete a;
}

void PuedeEliminarAnterior() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(10);
	a->agregar(20);
	a->agregar(30);
	ASSERT_EQ(to_s(a), "[30, 20, 10]");
	a->eliminar(10);
	ASSERT_EQ(to_s(a), "[30, 20]");
	delete a;
}

void PuedeEliminarActual() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(10);
	a->agregar(20);
	a->agregar(30);
	ASSERT_EQ(to_s(a), "[30, 20, 10]");
	a->eliminar(30);
	ASSERT_EQ(to_s(a), "[20, 10]");
	delete a;
}

void RetrocederPermiteRemarcar() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(10);
	a->agregar(20);
	a->agregar(30);
	a->marcar();
	a->siguiente();
	ASSERT_EQ(to_s(a), "[20, 10, 30*]");
	a->retroceder();
	a->marcar();
	ASSERT_EQ(to_s(a), "[30*, 20, 10]");
	a->retroceder();
	ASSERT_EQ(to_s(a), "[10, 30*, 20]");
	delete a;
}

void AnilloDeAnillo() {
	// Nota: si no compila es porque se uso la asignacion de T
	// cosa que no estaba permitido segun el .h
	Anillo<Anillo<int> > a;
	a.agregar(Anillo<int>());
	Anillo<Anillo<int> > b(a);
}

void IgualdadRespetaCantidad() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);

	Anillo<int>* b = new Anillo<int>();
	b->agregar(1);
	b->agregar(1);

	ASSERT(!(*a == *b));

	delete a;
	delete b;
}

void IgualdadRespetaOrden() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->agregar(3);

	Anillo<int>* b = new Anillo<int>();
	b->agregar(1);
	b->agregar(2);
	b->agregar(3);

	Anillo<int>* c = new Anillo<int>();
	c->agregar(2);
	c->agregar(3);
	c->agregar(1);

	ASSERT(*a == *b);
	ASSERT(!(*a == *c));

	delete a;
	delete b;
	delete c;
}

void IgualConMismaInstancia() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(*a == *a);
	delete a;
}

void IgualdadConVacios() {
	Anillo<int>* a = new Anillo<int>();
	Anillo<int>* b = new Anillo<int>();
	ASSERT(*a == *b);
	delete a;
	delete b;
}

void IgualdadRespetaMarcado() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->marcar();
	a->agregar(3);

	Anillo<int>* b = new Anillo<int>();
	b->agregar(1);
	b->agregar(2);
	b->marcar();
	b->agregar(3);

	Anillo<int>* c = new Anillo<int>();
	c->agregar(1);
	c->agregar(2);
	c->agregar(3);
	c->marcar();

	Anillo<int>* d = new Anillo<int>();
	d->agregar(1);
	d->agregar(2);
	d->agregar(3);

	ASSERT(*a == *b);
	ASSERT(!(*a == *c));
	ASSERT(!(*a == *d));

	delete a;
	delete b;
	delete c;
	delete d;
}

void IgualdadRespetaMarcadoConRepeticion()
{
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(1);
	a->marcar();

	Anillo<int>* b = new Anillo<int>();
	b->agregar(1);
	b->marcar();
	b->agregar(1);

	ASSERT(!(*a == *b));

	delete a;
	delete b;
}

// fin borrar

int main(void) {
	RUN_TEST(AnilloNuevoEsVacio);
	RUN_TEST(AnilloUnitarioAlEliminarQuedaVacio);
	RUN_TEST(AnilloUnitarioDaSiguiente);
	RUN_TEST(MostrarAnilloVacio);
	// borrar
	RUN_TEST(AnilloPuedeRotarVariasVeces);
	RUN_TEST(AnilloUnitarioCicla);
	RUN_TEST(UltimoEnAgregarEsElActual);
	RUN_TEST(MasNuevosQuedanPrimeros);
	RUN_TEST(AnilloConDosCicla);
	RUN_TEST(AnilloSacaNoSiguiente);
	RUN_TEST(MostrarAnillo);
	RUN_TEST(AnillosClonadoPreservaMarcado);
	RUN_TEST(PuedeEliminarMarcado);
	RUN_TEST(PuedeEliminarSiguiente);
	RUN_TEST(PuedeEliminarAnterior);
	RUN_TEST(PuedeEliminarActual);

	RUN_TEST(IgualdadRespetaCantidad);
	RUN_TEST(IgualdadRespetaOrden);
	RUN_TEST(IgualdadRespetaMarcado);
	RUN_TEST(IgualConMismaInstancia);
	RUN_TEST(IgualdadConVacios);
	RUN_TEST(IgualdadRespetaMarcadoConRepeticion);

	RUN_TEST(RetrocederPermiteRemarcar);
	RUN_TEST(AnilloDeAnillo);
	RUN_TEST(MostrarAnillo2);
	return 0;
}
