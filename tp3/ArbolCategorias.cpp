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

void ArbolCategorias::DatosCat::agregarCat(String c){
    this->_categoria = c;
}

void ArbolCategorias::DatosCat::agregarId(int i){
    this->_id = i;
}

void ArbolCategorias::DatosCat::agregarHijos(ItCategorias h){
    this->_hijos = h;
}

void ArbolCategorias::DatosCat::agregarPadre(DatosCat* p){
    this->_padre = p;
}

void ArbolCategorias::DatosCat::agregarAltura(int a){
    this->_altura = a;
}



ArbolCategorias::DatosCat* ArbolCategorias::obtenerAC(const Categoria c) const
{
    return _familia.Obtener(c);
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

    return _familia.Obtener(c)->dameId();
}

int ArbolCategorias::alturaCatAC(const Categoria c) const
{
    return _familia.Obtener(c)->dameAltura();

}

ArbolCategorias::ItCategorias& ArbolCategorias::hijosAC(const Categoria& c) const
{
    return _familia.Obtener(c)->dameHijos();
}

Categoria ArbolCategorias::padreAC(const Categoria& c) const
{
    return _familia.Obtener(c)->damePadre().dameCat();
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
