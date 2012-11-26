#include "ArbolCategorias.h"

ArbolCategorias::ArbolCategorias()
{
}

ArbolCategorias::ArbolCategorias(const Categoria& raiz)
{
	_cantidad = 1;
	_alturaMax = 1;
	Conj<DatosCat*> hijos = Conj<DatosCat*>();
	DatosCat* dato = new DatosCat(raiz, 1, 1, hijos, NULL);
	_raiz = dato;
}

ArbolCategorias::ArbolCategorias(const ArbolCategorias& arbol)
{

}

ArbolCategorias::~ArbolCategorias()
{

}

ArbolCategorias::DatosCat::DatosCat()
{

}

ArbolCategorias::DatosCat::DatosCat(const Categoria cat, int id, int altura, Conj<DatosCat*> hijos, DatosCat* padre)
{
    _categoria = cat;
    _id = id;
    _altura = altura;
    _hijos = hijos;
    _padre = padre;
}

ArbolCategorias::DatosCat::~DatosCat()
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

ArbolCategorias::ItHijos& ArbolCategorias::DatosCat::dameHijos() const
{
    ItHijos *res = new ItHijos();
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

void ArbolCategorias::DatosCat::agregarHijos(Conj<DatosCat*> h){
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
    ItCategorias itCat = ItCategorias(_categorias);
    return itCat;
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

ArbolCategorias::ItHijos& ArbolCategorias::hijosAC(const Categoria& c) const
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

ArbolCategorias::ItCategorias::ItCategorias(Lista<DatosCat> ldc)
{
    _itLista = ldc.CrearIt();
    _tamanio = ldc.Longitud();
}

ArbolCategorias::ItCategorias::~ItCategorias()
{

}

bool ArbolCategorias::ItCategorias::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

Categoria ArbolCategorias::ItCategorias::Siguiente() const
{
    return _itLista.Siguiente().dameCat();
}

void ArbolCategorias::ItCategorias::Avanzar()
{
    _itLista.Avanzar();
}

int ArbolCategorias::ItCategorias::tamanio() const
{
    return _tamanio;
}

bool ArbolCategorias::ItCategorias::operator==(const ItCategorias& otro) const
{
    return false;
}

ArbolCategorias::ItHijos::ItHijos()
{

}

ArbolCategorias::ItHijos::ItHijos(Conj<DatosCat*> cdc)
{
    _itConj = cdc.CrearIt();
    _tamanio = cdc.Cardinal();
}

ArbolCategorias::ItHijos::~ItHijos()
{

}

bool ArbolCategorias::ItHijos::HaySiguiente() const
{
    return _itConj.HaySiguiente();
}

Categoria ArbolCategorias::ItHijos::Siguiente() const
{
    return _itConj.Siguiente()->dameCat();
}

void ArbolCategorias::ItHijos::Avanzar()
{
    _itConj.Avanzar();
}

int ArbolCategorias::ItHijos::tamanio() const
{
    return _tamanio;
}

bool ArbolCategorias::ItHijos::operator==(const ItHijos& otro) const
{
    return false;
}
