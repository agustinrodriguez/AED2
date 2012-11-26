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

ArbolCategorias::ItCategorias& ArbolCategorias::dameHijos(const DatosCat& dc) const
{
    ItCategorias *res = new ItCategorias();
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

ArbolCategorias::ItCategorias ArbolCategorias::categoriasAC() const
{
    ItCategorias *res = new ItCategorias();
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

ArbolCategorias::ItCategorias& ArbolCategorias::hijosAC(const Categoria& c) const
{
    ItCategorias *res = new ItCategorias();
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

ArbolCategorias::ItCategorias::ItCategorias()
{

}

ArbolCategorias::ItCategorias::~ItCategorias()
{

}

bool ArbolCategorias::ItCategorias::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

Categoria& ArbolCategorias::ItCategorias::Siguiente() const
{
    // DatosCat *dc = _itLista.Siguiente();

    Categoria *res = new Categoria();
    return *res;
}

void ArbolCategorias::ItCategorias::Avanzar()
{
    _itLista.Avanzar();
}

void ArbolCategorias::ItCategorias::EliminarSiguiente()
{
    _itLista.EliminarSiguiente();
}

void ArbolCategorias::ItCategorias::AgregarComoSiguiente(const Categoria& elem)
{
//    _itLista.AgregarComoSiguiente(elem);
}


bool ArbolCategorias::ItCategorias::operator==(const ItCategorias& otro) const
{
    return false;
}
