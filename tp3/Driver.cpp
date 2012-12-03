#include "Driver.h"

#include <iostream>
#include <sstream>

Driver::Driver() {
    arbol = NULL;
    sistema = NULL;
}

Driver::~Driver() {
    // el arbol de categorías se destruye si fue creado
    if (arbol != NULL)
        delete arbol;

    // el linklinkit se destruye si fue creado
    if (sistema != NULL)
        delete sistema;
}

void Driver::nuevoArbol(const Categoria& raiz)
{
    if (arbol != NULL)
        delete arbol;
    arbol = new ArbolCategorias(raiz);
}

void Driver::agregarCategoria(const Categoria& c, const Categoria& h)
{
    arbol->agregarAC(c,h);
}

const Categoria& Driver::raiz()
{
    return arbol->raizAC();
}

int Driver::id(const Categoria& c)
{
    ArbolCategorias::DatosCat *dc = arbol->obtenerAC(c);
    return dc->dameId();
}

int Driver::cantCategoriasHijas(const Categoria& c)
{
    int i = 0;
    ArbolCategorias::ItHijos it = arbol->hijosAC(c);
    while(it.HaySiguiente())
    {
        ++i;
        it.Avanzar();
    }
    return i;
}

const Categoria& Driver::obtenerIesimaCategoriaHija(const Categoria& c, int i)
{
    int j = 0;
    ArbolCategorias::ItHijos it = arbol->hijosAC(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.Siguiente();
}

void Driver::nuevoLink(const Link& l, const Categoria& c)
{
    if (sistema == NULL)
        sistema = new LinkLinkIt(arbol);

    sistema->nuevoLinkLli(l,c);
}

void Driver::acceso(const Link& l, Fecha f)
{
    sistema->accesosRecientesDia(l, f);
}

int Driver::cantLinks(const Categoria& c)
{
    return sistema->cantLinks(c);
}

const Link& Driver::obtenerIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i)
{
    int j = 0;
    LinkLinkIt::itPunLinks it = sistema->linksOrdenadosPorAccesos(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.Siguiente()->dameLink();
}

const Categoria& Driver::obtenerCategoriaIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i)
{
    int j = 0;
    LinkLinkIt::itPunLinks it = sistema->linksOrdenadosPorAccesos(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.Siguiente()->dameCatDLink().dameCat();
}

int Driver::obtenerCantidadAccesosIesimoLinkOrdenadoPorAccesos(const Categoria& c, int i)
{
    int j = 0;
    LinkLinkIt::itPunLinks it = sistema->linksOrdenadosPorAccesos(c);
    while(j < i)
    {
        ++j;
        it.Avanzar();
    }
    return it.Siguiente()->dameCantAccesos();
}
