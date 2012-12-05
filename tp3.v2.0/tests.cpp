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
ArbolCategorias a = ArbolCategorias(raiz);
ASSERT_EQ(a.alturaAC(), 1);
ASSERT_EQ(a.obtenerAC(raiz)->dameId(),1);
ASSERT_EQ(a.obtenerAC(raiz)->dameCat(),raiz);
ASSERT_EQ(a.dameCantidad(),1);
ASSERT_EQ(a.alturaAC(),1);
Categoria c1 = "cat1";
Categoria c2 = "cat2";
a.agregarAC(c1,raiz);
ASSERT_EQ(a.dameCantidad(),2);
ASSERT(a.esSubCategoria(raiz,raiz));
ASSERT_STR_EQ(a.obtenerAC(c1)->damePadre()->dameCat(), raiz);
ASSERT(a.esSubCategoria(raiz,c1));
ASSERT(!(a.esta(c2)));
ASSERT_EQ(a.alturaCatAC(c1),2);
ASSERT_EQ(a.idAC(c1),2);
ASSERT_EQ(a.alturaAC(),2);
ASSERT_EQ(a.dameCantidad(),2);
Categoria c3 = a.categoriasAC().Siguiente();
ASSERT_EQ(a.categoriasAC().Siguiente() == "categoria1",true);
ArbolCategorias::ItCategorias itA = ArbolCategorias::ItCategorias(a.categoriasAC());
ASSERT(itA == a.categoriasAC());
ASSERT(a.hijosAC(raiz).Siguiente() == c1);

}

void arbolNuevoConRaizTieneHijoVacio(){
    Categoria c,d;
    c= "hola";
    d= "chau";
    ArbolCategorias *a = new ArbolCategorias(c);
    ASSERT_EQ(a->alturaAC(),1);
    ASSERT_EQ(a->idAC(c),1);
    ASSERT_EQ(a->raizAC(),c);
    ASSERT_EQ(a->dameCantidad(),1);
    ASSERT_EQ(a->esta(c),true);
    ASSERT_EQ(a->esta(d),false);
    a->agregarAC(d,c);
    ASSERT_EQ(a->esta(c),true);
    ASSERT_EQ(a->esta(d),true);
    ASSERT_EQ(a->esSubCategoria(c,d),true);
    delete a;
}
//void datosLinkNuevoEsVacio(){
//    LinkLinkIt::DatosLink* dl = new LinkLinkIt::DatosLink();
//    ASSERT_EQ(dl->dameAccesos().Longitud(),0);
//    String l = "link";
//    dl->nuevoLink(l);
//    int car = 0;
//    dl->nuevoCantAccesosRecientes(car);
//    Lista<LinkLinkIt::Acceso> ita = Lista<LinkLinkIt::Acceso>();
//    dl->nuevoAccesos(ita);
//    ArbolCategorias::DatosCat* dc = new ArbolCategorias::DatosCat();
//    dl->nuevaCat(dc);
//    ASSERT_EQ(dl->dameLink(),l);
//    ASSERT_EQ(dl->dameAccesos().Longitud(),0);
//    ASSERT_EQ(dl->dameCantAccesos(),car);
//    ASSERT_EQ(dl->dameCatDLink() == *dc, true);
//    delete dl;
//    delete dc;
//}

//void datosLinkConDatos(){
//    ArbolCategorias::DatosCat* dc = new ArbolCategorias::DatosCat();
//    String l = "link";
//    Lista<LinkLinkIt::Acceso> la = Lista<LinkLinkIt::Acceso>();
//    LinkLinkIt::DatosLink* dl = new LinkLinkIt::DatosLink(l, dc, la, 0);
//    ASSERT_EQ(dl->dameCatDLink() == * dc, true);
//    ASSERT_EQ(dl->dameAccesos() == la, true);
//    ASSERT_EQ(dl->dameCantAccesos(), 0);
//    ASSERT_EQ(dl->dameLink(),l);
//    LinkLinkIt::DatosLink* dl2 = new LinkLinkIt::DatosLink(l, dc, la, 0);
//    LinkLinkIt::DatosLink* dl3 = new LinkLinkIt::DatosLink(l, dc, la, 3);
//    Lista<LinkLinkIt::Acceso> lb = Lista<LinkLinkIt::Acceso>();
//    LinkLinkIt::Acceso* ac = new LinkLinkIt::Acceso(3,4);
//    lb.AgregarAtras(*ac);
//    LinkLinkIt::DatosLink* dl4 = new LinkLinkIt::DatosLink(l, dc, lb, 0);
//    ASSERT_EQ(*dl == *dl2,true);
//    ASSERT_EQ(*dl == *dl3,false);
//    ASSERT_EQ(*dl == *dl4,false);
//    Categoria cat = "cat2";
//    Conj<ArbolCategorias::DatosCat*> conj1 = Conj<ArbolCategorias::DatosCat*>();
//    ArbolCategorias::DatosCat* dc2 = new ArbolCategorias::DatosCat(cat, 2, 3, conj1 , NULL);
//    LinkLinkIt::DatosLink* dl5 = new LinkLinkIt::DatosLink(l, dc2, lb, 0);
//    ASSERT_EQ(*dl == *dl5, false);
//    delete dc;
//    delete dc2;
//    delete dl;
//    delete dl2;
//    delete dl3;
//    delete dl4;
//    delete dl5;
//    delete ac;
//}

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
    delete a;
    delete b;
    delete c;
    delete d;
    delete e;
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
    delete a;
    delete b;
    delete c;
    delete d;
    delete e;
    }
void testLinkNuevo(){
    Categoria cat = "informacion";
    Categoria c2 = "InformacionAnimales";
    ArbolCategorias *acat = new ArbolCategorias(cat);
    LinkLinkIt::Acceso* a = new LinkLinkIt::Acceso(3,7);
    Lista<LinkLinkIt::Acceso> *listaAccesos = new Lista<LinkLinkIt::Acceso>();
    String miLink = "test";
    Conj<ArbolCategorias::DatosCat*> conj = Conj<ArbolCategorias::DatosCat*>();
    //ArbolCategorias::DatosCat* dc = new ArbolCategorias::DatosCat(cat,323,1,conj,NULL);
    LinkLinkIt::DatosLink* dl = new LinkLinkIt::DatosLink(miLink,cat,*listaAccesos,1);
    acat->agregarAC(c2,cat);
    LinkLinkIt *lli = new LinkLinkIt(acat);
    delete a;
    delete dl;
    delete lli;
    delete listaAccesos;
    delete acat;
}

void LinkLinkItNuevo(){
    Categoria cat = "cat";
    ArbolCategorias *acat = new ArbolCategorias(cat);
    LinkLinkIt lli = LinkLinkIt(acat);
    lli.nuevoLinkLli("link", "cat");
    ASSERT_EQ(lli.categoriaLink("link"), "cat");
    ASSERT_EQ(lli.cantLinks("cat"), 1);
    lli.accederLli("link", 120);
    ASSERT_EQ(lli.fechaActual(), 120);
    ASSERT_EQ(lli.fechaUltimoAcceso("link"), 120);
    ASSERT_EQ(lli.accesosRecientesDia("link", 120), 1);
    lli.nuevoLinkLli("linkkk", "cat");
    ASSERT_EQ(lli.linksLli().Siguiente() == "link", true);
    lli.accederLli("linkkk", 122);
    lli.accederLli("linkkk", 122);
    lli.accederLli("linkkk", 122);
    lli.accederLli("linkkk", 122);
    lli.accederLli("link", 123);
    ASSERT_EQ(lli.fechaActual(), 123);
    ASSERT_EQ(lli.accesosRecientesDia("link", 122), 0);
    ASSERT_EQ(lli.accesosRecientesDia("linkkk", 122), 4);
    ASSERT_EQ(lli.fechaUltimoAcceso("link"), 123);
    ASSERT_EQ(lli.fechaUltimoAcceso("linkkk"), 122);
    ASSERT_EQ(lli.accesosRecientesDia("link", 123), 1);
    lli.nuevoLinkLli("link1", "cat");
    lli.nuevoLinkLli("link2", "cat");
    lli.nuevoLinkLli("link3", "cat");
    ASSERT_EQ(lli.cantLinks("cat"),5);
    LinkLinkIt::itLinks itL = LinkLinkIt::itLinks(lli.linksLli());
    ASSERT(itL == lli.linksLli());
    LinkLinkIt::itPunLinks itP = LinkLinkIt::itPunLinks(lli.linksOrdenadosPorAccesos("cat"));
    Link l = itP.SiguienteLink();
    ASSERT_EQ(itP.SiguienteLink() == "linkkk", true);
    ASSERT_EQ(itP.SiguienteCantidadAccesosDelLink(),4);
    itP.Avanzar();
    ASSERT_EQ(itP.SiguienteLink() == "link",true);
    LinkLinkIt::itPunLinks itP2 = LinkLinkIt::itPunLinks(lli.linksOrdenadosPorAccesos("cat"));
    ASSERT_EQ(itP2.SiguienteLink() == "linkkk", true);
    delete acat;
}


void LLIGigante(){
    Categoria cat = "cat";
    ArbolCategorias *acat = new ArbolCategorias(cat);
    acat->agregarAC("miniCat", cat);
    acat->agregarAC("miniCat2", cat);
    acat->agregarAC("miniCat3", cat);
    acat->agregarAC("miniCat4", "miniCat2");
    acat->agregarAC("miniCat5", "miniCat4");
    ArbolCategorias *acat2 = new ArbolCategorias(cat);
    acat2->agregarAC("miniCat33", cat);
    acat2->agregarAC("miniCat2", cat);
    acat2->agregarAC("miniCat3", cat);
    acat2->agregarAC("miniCat4", "miniCat2");
    acat2->agregarAC("miniCat5", "miniCat4");
    LinkLinkIt lli = LinkLinkIt(acat);
    lli.nuevoLinkLli("link", "cat");
    ASSERT_EQ(lli.categoriaLink("link"), "cat");
    ASSERT_EQ(lli.cantLinks("cat"), 1);
    lli.accederLli("link", 120);
    ASSERT(!(*acat == *acat2));
    ASSERT_EQ(lli.fechaActual(), 120);
    ASSERT_EQ(lli.fechaUltimoAcceso("link"), 120);
    ASSERT_EQ(lli.accesosRecientesDia("link", 120), 1);
    delete acat;
    delete acat2;
}
void testAgregarLink(){
    Categoria cat = "cat";
    ArbolCategorias *acat = new ArbolCategorias(cat);
    acat->agregarAC("miniCat",cat);
    acat->agregarAC("miniCat2","miniCat");
    LinkLinkIt lli = LinkLinkIt(acat);
    lli.nuevoLinkLli("miLink","miniCat2");
    ASSERT_EQ(lli.categoriaLink("miLink"),"miniCat2");
    delete acat;
}

int main(void) {
    RUN_TEST(arbolNuevoEsVacio);
    RUN_TEST(arbolNuevoConRaizTieneHijoVacio);
    RUN_TEST(accesoTest);
    RUN_TEST(accesoTestConConstr);
    RUN_TEST(LinkLinkItNuevo);
    RUN_TEST(testLinkNuevo);
    RUN_TEST(LLIGigante);
    RUN_TEST(testAgregarLink);
	return 0;
}
