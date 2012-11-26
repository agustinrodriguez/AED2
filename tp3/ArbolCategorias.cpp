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

const Categoria& ArbolCategorias::DatosCat::dameCat() const
{
    return _categoria;

}

int ArbolCategorias::DatosCat::dameId() const
{
    return _id;
}

int ArbolCategorias::DatosCat::dameAltura() const
{
    return _altura;
}

ArbolCategorias::ItCategorias& ArbolCategorias::DatosCat::dameHijos() const
{
    ItCategorias *res = new ItCategorias();
    return *res;
}
const ArbolCategorias::DatosCat& ArbolCategorias::DatosCat::damePadre() const
{
    return *_padre;
}

ArbolCategorias::DatosCat* ArbolCategorias::obtenerAC(const Categoria c) const
{
    // DatosCat hola = _familia.Obtener(c); MODIFICAR EL DICCIONARIO PARA Q EN VEZ DE T DEVUELVA DATOSCAT O DATOSLINK
    DatosCat *res = new DatosCat();
    return res;
}

ArbolCategorias::ItCategorias ArbolCategorias::categoriasAC() const
{
    return _categorias;
}

const Categoria& ArbolCategorias::raizAC() const
{

    return (*_raiz).dameCat();
}

int ArbolCategorias::idAC(const Categoria& c) const
{

    //return _familia.Obtener(c).dameId(); EL DICCIONARIO
    return 0;
}

int ArbolCategorias::alturaCatAC(const Categoria c) const
{
    //return (*_familia.Obtener(c)).dameAltura(); EL DICCIONARIO
    return 0;
}

ArbolCategorias::ItCategorias& ArbolCategorias::hijosAC(const Categoria& c) const
{
    ItCategorias *res = new ItCategorias();
    return *res;
}

Categoria ArbolCategorias::padreAC(const Categoria& c) const
{
    //return (*_familia.Obtener(c)).damePadre(); EL DICCIONARIO
    return "CategoriaDePrueba";
}

int ArbolCategorias::alturaAC() const
{
    return _alturaMax;
}

void ArbolCategorias::agregarAC(const Categoria c, const Categoria cpadre)
{

}

bool ArbolCategorias::esta(const Categoria c) const
{
    return _familia.Def(c);
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
