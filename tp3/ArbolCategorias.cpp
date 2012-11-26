#include "ArbolCategorias.h"

ArbolCategorias::ArbolCategorias()
{
}

ArbolCategorias::ArbolCategorias(const Categoria& raiz)
{
	_cantidad = 1;
	_alturaMax = 1;
	DatosCat* dato = new DatosCat();
	dato->_id = 1;
	dato->_categoria = raiz;
	dato->_altura = 1;
	//dato->_hijos = Conj<Categoria>::Conj();
	dato->_padre = NULL;
}

ArbolCategorias::ArbolCategorias(const ArbolCategorias& arbol)
{

}

ArbolCategorias::~ArbolCategorias()
{

}

const Categoria& ArbolCategorias::dameCat(const DatosCat& dc) const
{
    Categoria *res = new Categoria();
    return *res;
}

int ArbolCategorias::dameId(const DatosCat& dc) const
{
    return 0;
}

int ArbolCategorias::dameAltura(const DatosCat& dc) const
{
    return 0;
}

ArbolCategorias::DatosCat::ItDatosCat& ArbolCategorias::dameHijos(const DatosCat& dc) const
{
    DatosCat::ItDatosCat *res = new DatosCat::ItDatosCat();
    return *res;
}
const ArbolCategorias::DatosCat& ArbolCategorias::damePadre(const DatosCat& dc) const
{
    DatosCat *res = new DatosCat();
    return *res;
}

ArbolCategorias::DatosCat* ArbolCategorias::obtenerAC(const Categoria c) const
{
    DatosCat *res = new DatosCat();
    return res;
}

ArbolCategorias::DatosCat::ItDatosCat ArbolCategorias::categoriasAC() const
{
    DatosCat::ItDatosCat *res = new DatosCat::ItDatosCat();
    return *res;
}

const Categoria& ArbolCategorias::raizAC() const
{
    Categoria *res = new Categoria();
    return *res;
}

int ArbolCategorias::idAC(const Categoria& c) const
{
    return 0;
}

int ArbolCategorias::alturaCatAC(const Categoria c) const
{
    return 0;
}

ArbolCategorias::DatosCat::ItDatosCat& ArbolCategorias::hijosAC(const Categoria& c) const
{
    DatosCat::ItDatosCat *res = new DatosCat::ItDatosCat();
    return *res;
}

Categoria ArbolCategorias::padreAC(const Categoria& c) const
{
    return "CategoriaDePrueba";
}

int ArbolCategorias::alturaAC() const
{
    return 0;
}

void ArbolCategorias::agregarAC(const Categoria c, const Categoria cpadre)
{

}

bool ArbolCategorias::esta(const Categoria c) const
{
    return false;
}

bool ArbolCategorias::esSubCategoria(const Categoria c, const Categoria predecesor) const
{
    return false;
}

ArbolCategorias::DatosCat::ItDatosCat::ItDatosCat()
{

}
