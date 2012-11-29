#include "Driver.h"
#include <stdarg.h>
#include "LinkLinkIt.h"
#include "ArbolCategorias.h"

using namespace std;
using namespace aed2;

// auxiliares para tests
#include <iostream>
#include <sstream>
void mt_assert(bool expr, string lhs, string rhs, int line) { if (!expr) {ostringstream os;os << "error en linea " << line << endl;os << "   se esperaba: " << rhs << endl;os << "     se obtuvo: " << lhs;throw os.str();} }
void mt_str_assert(string lhs, string rhs, int line) { if (lhs.compare(rhs) != 0) { ostringstream os;os << "error en linea " << line << endl;os << "   se esperaba: " << rhs << endl;os << "     se obtuvo: " << lhs;throw os.str();} }
#define RUN_TEST(test) {\
	{bool ok = true;\
	cout << #test << "..." << flush;\
	try { test(); }\
	catch (string& msg) { ok = false; cout << msg; } \
	catch (...) { ok = false; cout << "error"; }\
	if (ok) { cout << "ok"; }\
	cout << endl << flush;\
	}\
}
#define ASSERT_EQ(lhs, rhs) {{ostringstream lhss, rhss;lhss << (lhs);rhss << (rhs);mt_assert((lhs) == (rhs), lhss.str(), rhss.str(), __LINE__);}}
#define ASSERT(expr) { mt_assert((expr), "false", "true", __LINE__); }
#define ASSERT_STR_EQ(lhs, rhs) { mt_str_assert(string((lhs)), string((rhs)), __LINE__); }
// fin auxiliares para tests

/**
 * Permite construir una lista de strings de forma comoda.
 * l("lorem", "ipsum", NULL) equivale a la lista ["lorem", "ipsum"]
 * l(NULL) equivale a la lista vacia.
 *
 * siembre es necesario poner un NULL para indicar el final de la lista
 */

void arbolNuevoEsVacio(){
Categoria raiz = "categoria1";
ArbolCategorias *a = new ArbolCategorias(raiz);
ASSERT_EQ(a->alturaAC(), 1);
ASSERT_EQ(a->obtenerAC(raiz)->dameId(),1);
ASSERT_EQ(a->obtenerAC(raiz)->dameCat(),raiz);
ASSERT_EQ(a->categoriasAC().tamanio(),1);
ASSERT_EQ(a->alturaAC(),1);
Categoria c1 = "cat1";
Categoria c2 = "cat2";
a->agregarAC(c1,raiz);
ASSERT_EQ(a->hijosAC(raiz).tamanio(),1);
ASSERT(a->esSubCategoria(raiz,raiz));

ASSERT_STR_EQ(a->obtenerAC(c1)->damePadre()->dameCat(), raiz);

ASSERT(a->esSubCategoria(raiz,c1));
ASSERT(!(a->esta(c2)));
ASSERT_EQ(a->alturaCatAC(c1),2);
ASSERT_EQ(a->idAC(c1),2);
ASSERT_EQ(a->alturaAC(),2);
ASSERT_EQ(a->categoriasAC().tamanio(),2);
delete a;
}

void arbolNuevoConRaizTieneHijoVacio(){
    Categoria c,d;
    c= "hola";
    d= "chau";
    ArbolCategorias *a = new ArbolCategorias(c);
    ASSERT_EQ(a->alturaAC(),1);
    ASSERT_EQ(a->idAC(c),1);
    ASSERT_EQ(a->raizAC(),c);
    ASSERT_EQ(a->categoriasAC().tamanio(),1);
    ASSERT_EQ(a->esta(c),true);
    ASSERT_EQ(a->esta(d),false);
    a->agregarAC(d,c);
    ASSERT_EQ(a->hijosAC(c).tamanio(),1);
    ASSERT_EQ(a->esta(c),true);
    ASSERT_EQ(a->esta(d),true);
    ASSERT_EQ(a->esSubCategoria(c,d),true);
    delete a;
}

void datosLinkNuevoEsVacio(){
    LinkLinkIt::DatosLink* dl = new LinkLinkIt::DatosLink();
    ASSERT_EQ(dl->dameAccesos().Longitud(),0);
    String l = "link";
    dl->nuevoLink(l);
    int car = 0;
    dl->nuevoCantAccesosRecientes(car);
    Lista<LinkLinkIt::Acceso> ita = Lista<LinkLinkIt::Acceso>();
    dl->nuevoAccesos(ita);
    ArbolCategorias::DatosCat* dc = new ArbolCategorias::DatosCat();
    dl->nuevaCat(dc);
    ASSERT_EQ(dl->dameLink(),l);
    ASSERT_EQ(dl->dameAccesos().Longitud(),0);
    ASSERT_EQ(dl->dameCantAccesos(),car);
    ASSERT_EQ(dl->dameCatDLink() == *dc, true);
    delete dl;
    delete dc;
}

void datosLinkConDatos(){
    ArbolCategorias::DatosCat* dc = new ArbolCategorias::DatosCat();
    String l = "link";
    Lista<LinkLinkIt::Acceso> la = Lista<LinkLinkIt::Acceso>();
    LinkLinkIt::DatosLink* dl = new LinkLinkIt::DatosLink(l, dc, la, 0);
    ASSERT_EQ(dl->dameCatDLink() == * dc, true);
    ASSERT_EQ(dl->dameAccesos() == la, true);
    ASSERT_EQ(dl->dameCantAccesos(), 0);
    ASSERT_EQ(dl->dameLink(),l);
    LinkLinkIt::DatosLink* dl2 = new LinkLinkIt::DatosLink(l, dc, la, 0);
    LinkLinkIt::DatosLink* dl3 = new LinkLinkIt::DatosLink(l, dc, la, 3);
    Lista<LinkLinkIt::Acceso> lb = Lista<LinkLinkIt::Acceso>();
    LinkLinkIt::Acceso* ac = new LinkLinkIt::Acceso(3,4);
    lb.AgregarAtras(*ac);
    LinkLinkIt::DatosLink* dl4 = new LinkLinkIt::DatosLink(l, dc, lb, 0);
    ASSERT_EQ(*dl == *dl2,true);
    ASSERT_EQ(*dl == *dl3,false);
    ASSERT_EQ(*dl == *dl4,false);
    Categoria cat = "cat2";
    Conj<ArbolCategorias::DatosCat*> conj1 = Conj<ArbolCategorias::DatosCat*>();
    ArbolCategorias::DatosCat* dc2 = new ArbolCategorias::DatosCat(cat, 2, 3, conj1 , NULL);
    LinkLinkIt::DatosLink* dl5 = new LinkLinkIt::DatosLink(l, dc2, lb, 0);
    ASSERT_EQ(*dl == *dl5, false);
    delete dc;
    delete dc2;
    delete dl;
    delete dl2;
    delete dl3;
    delete dl4;
    delete dl5;
}

void accesoTest(){
    LinkLinkIt::Acceso* a = new LinkLinkIt::Acceso();
    LinkLinkIt::Acceso* b = new LinkLinkIt::Acceso();
    LinkLinkIt::Acceso* c = new LinkLinkIt::Acceso();
    LinkLinkIt::Acceso* d = new LinkLinkIt::Acceso();
    LinkLinkIt::Acceso* e = new LinkLinkIt::Acceso();
    a->guardoAcceso(2);
    a->guardoDia(3);
    b->guardoAcceso(2);
    b->guardoDia(3);
    c->guardoAcceso(2);
    c->guardoDia(99);
    d->guardoAcceso(24);
    d->guardoDia(3);
    e->guardoAcceso(23);
    e->guardoDia(32);
    ASSERT_EQ(*a==*b,true);
    ASSERT_EQ(*a==*c,false);
    ASSERT_EQ(*a==*d,false);
    ASSERT_EQ(*a==*c,false);
    ASSERT_EQ(*a==*e,false);
}

void accesoTestConConstr(){
    LinkLinkIt::Acceso* a = new LinkLinkIt::Acceso(2,3);
    LinkLinkIt::Acceso* b = new LinkLinkIt::Acceso(2,3);
    LinkLinkIt::Acceso* c = new LinkLinkIt::Acceso(2,99);
    LinkLinkIt::Acceso* d = new LinkLinkIt::Acceso(24,3);
    LinkLinkIt::Acceso* e = new LinkLinkIt::Acceso(23,32);
    ASSERT_EQ(*a==*b,true);
    ASSERT_EQ(*a==*c,false);
    ASSERT_EQ(*a==*d,false);
    ASSERT_EQ(*a==*c,false);
    ASSERT_EQ(*a==*e,false);
}

void datosCatNuevo(){
    ArbolCategorias::DatosCat* dc = new ArbolCategorias::DatosCat();
    dc->agregarAltura(1);
    dc->agregarCat("cat");
    dc->agregarId(323);
    dc->agregarPadre(NULL);
    Conj<ArbolCategorias::DatosCat*> conj = Conj<ArbolCategorias::DatosCat*>();
    dc->agregarHijos(conj);
    ASSERT_EQ(dc->dameAltura(),1);
    ASSERT_EQ(dc->dameCat() == "cat",true);
    ASSERT_EQ(dc->dameHijos().tamanio(),0);
    ASSERT_EQ(dc->damePadre() == NULL, true);
    ArbolCategorias::DatosCat* dc1 = new ArbolCategorias::DatosCat("cat", 323, 1, conj, NULL);
    ASSERT_EQ(dc1->dameAltura(),1);
    ASSERT_EQ(dc1->dameCat() == "cat",true);
    ASSERT_EQ(dc1->dameHijos().tamanio(),0);
    ASSERT_EQ(dc1->damePadre() == NULL, true);
    ArbolCategorias::DatosCat* dc2 = new ArbolCategorias::DatosCat("cat", 323, 1, conj, dc);
    ASSERT_EQ(*dc == *dc1,true);
    ASSERT_EQ(*dc == *dc2,false);
    delete dc1;
    delete dc2;
    delete dc;
}

void LinkLinkItNuevo(){
    Categoria cat = "cat";
    ArbolCategorias *acat = new ArbolCategorias(cat);
    LinkLinkIt *lli = new LinkLinkIt(*acat);
    //ASSERT_EQ(lli->dameAcatLli() == *acat,true); FALTA HACER OPERATOR DE ACAT
    lli->nuevoLinkLli("link","cat");
    ASSERT_EQ(lli->categoriaLink("link"),"cat");
    ASSERT_EQ(lli->cantLinks("cat"),1);
    ASSERT_EQ(lli->categoriasLli().tamanio(),1);
    lli->accederLli("link",120);
    ASSERT_EQ(lli->fechaActual(),120);
    ASSERT_EQ(lli->fechaUltimoAcceso("link"),120);
    ASSERT_EQ(lli->accesosRecientesDia("link",122),1);
}

int main(void) {
        RUN_TEST(arbolNuevoEsVacio);
        RUN_TEST(arbolNuevoConRaizTieneHijoVacio);
        RUN_TEST(datosLinkNuevoEsVacio); //ANDA VERIFICAR DELETE
        RUN_TEST(datosLinkConDatos);//ANDA VERIFICAR DELETE
        RUN_TEST(accesoTest);//ANDA
        RUN_TEST(accesoTestConConstr);//ANDA
        RUN_TEST(datosCatNuevo);//ANDA VERIFICAR DELETE
        //RUN_TEST(LinkLinkItNuevo); //TIRA MUCHOS NUMERITOS JA
	return 0;
}
