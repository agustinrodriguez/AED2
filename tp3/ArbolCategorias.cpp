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
	_categorias = Lista<DatosCat>();
	_categorias.AgregarAdelante(*dato);
}

ArbolCategorias::ArbolCategorias(const ArbolCategorias& arbol)
{

}

ArbolCategorias::~ArbolCategorias()
{
    //Destruyo puntero a datoscat de la raiz
    delete _raiz;
    //Destruyo el diccionario
    _familia.~DiccTrie();
    //Destruyo la lista
    _categorias.~Lista();

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
    //destruyo el conjunto
    while(!(_hijos.EsVacio()))
    {
        delete _hijos.CrearIt().Siguiente();
        _hijos.CrearIt().Avanzar();
    }
    //destruyo categoria padre
    if(_padre != NULL)
    {
        _padre = NULL;
    }
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
    ItHijos *res = new ItHijos(_hijos);
    return *res;
}
ArbolCategorias::DatosCat* ArbolCategorias::DatosCat::damePadre() const
{
    return _padre;
}

void ArbolCategorias::DatosCat::agregarCat(String c){
    _categoria = c;
}

void ArbolCategorias::DatosCat::agregarId(int i){
    _id = i;
}

void ArbolCategorias::DatosCat::agregarHijo(ArbolCategorias::DatosCat* h){
    _hijos.Agregar(h);
}


void ArbolCategorias::DatosCat::agregarHijos(Conj<ArbolCategorias::DatosCat*> h){
    _hijos = h;
}

void ArbolCategorias::DatosCat::agregarPadre(DatosCat* p){
    _padre = p;
}

void ArbolCategorias::DatosCat::agregarAltura(int a){
    _altura = a;
}

void ArbolCategorias::DatosCat::copiarDc(ArbolCategorias::DatosCat otroDc){

}
bool ArbolCategorias::DatosCat::operator==(const DatosCat& otro) const{
    bool altura = dameAltura() == otro.dameAltura();
    bool cat = dameCat() == otro.dameCat();
    bool id = dameId() == otro.dameId();
    bool hijos = dameHijos() == otro.dameHijos();
    bool padre = damePadre() == otro.damePadre();
    return altura && cat && id && hijos && padre;
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
    return _familia.Obtener(c)->damePadre()->dameCat();
}

int ArbolCategorias::alturaAC() const
{
    return _alturaMax;
}

void ArbolCategorias::agregarAC(const Categoria c, const Categoria cpadre)
{
    DatosCat* puntPadre = _familia.Obtener(cpadre);
    if (puntPadre->dameAltura() == alturaAC())
    {
        _alturaMax++;
    }
    DatosCat tuplaA;
    tuplaA.agregarCat(c);
    tuplaA.agregarId(_cantidad + 1);
    tuplaA.agregarAltura(puntPadre->dameAltura()+1);
    Conj<DatosCat*> conj = Conj<DatosCat*>();
    tuplaA.agregarHijos(conj);
    tuplaA.agregarPadre(puntPadre);
    DatosCat* punt = &tuplaA;
    puntPadre->agregarHijo(punt);
    _cantidad++;
    _categorias.AgregarAtras(tuplaA);


}

bool ArbolCategorias::esta(const Categoria c) const
{
    return _familia.Def(c);
}

bool ArbolCategorias::esSubCategoria(const Categoria c, const Categoria predecesor) const
{
    bool res = false;
    if (predecesor == c)
    {
        res = true;
    }
    else
    {
        if(predecesor == raizAC())
        {
            res = false;
        }
        else
        {
            DatosCat* actual = _familia.Obtener(predecesor);
            DatosCat* puntC = _familia.Obtener(c)->damePadre();
            while((res == false && actual != NULL))
            {
                if(puntC->dameId() == actual->dameId())
                {
                    res = true;
                }
                else
                {
                    actual = actual->damePadre();
                }
            }
        }
    }
    return res;
}

ArbolCategorias::ItCategorias::ItCategorias()
{

}

ArbolCategorias::ItCategorias::ItCategorias(Lista<DatosCat> ldc)
{
    _itLista = ldc.CrearIt();
    _tamanio = ldc.Longitud();
}

ArbolCategorias::ItCategorias::ItCategorias(const ItCategorias& otroIt){
    _itLista = otroIt.dameIt();
    _tamanio = otroIt.tamanio();

}

ArbolCategorias::ItCategorias::~ItCategorias()
{
    //Destruyo la lista
    while(_itLista.HaySiguiente())
    {
        _itLista.EliminarSiguiente();
    }

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
/*
void ArbolCategorias::ItCategorias::copiarPos(ItCategorias otroIt){

}
*/
const Lista<ArbolCategorias::DatosCat>::Iterador ArbolCategorias::ItCategorias::dameIt() const{
    return _itLista;
}

bool ArbolCategorias::ItCategorias::operator==(const ItCategorias& otro) const
{
    bool iguales = true;
    iguales = _itLista == otro.dameIt();
    if(iguales)
    {
        iguales = _tamanio == otro.tamanio();
    }
    /*if(tamanio() == otro.tamanio())
    {
        iguales = true;
        ItCategorias itThis;
        ItCategorias itOtro;
        itThis.copiarPos(*this);
        itOtro.copiarPos(otro);
        while(itThis.HaySiguiente() && iguales)
        {
            iguales = itThis.Siguiente() == itOtro.Siguiente();
            itThis.Avanzar();
            itOtro.Avanzar();

        }
    }
    else
    {
        iguales = false;
    }*/
    return iguales;
}

ArbolCategorias::ItHijos::ItHijos()
{

}

ArbolCategorias::ItHijos::ItHijos(const ArbolCategorias::ItHijos& otroIt){
    _itConj= otroIt.dameIt();
    _tamanio = otroIt.tamanio();
}

ArbolCategorias::ItHijos::ItHijos(Conj<DatosCat*> cdc)
{
    _itConj = cdc.CrearIt();
    _tamanio = cdc.Cardinal();
}

ArbolCategorias::ItHijos::~ItHijos()
{
    //Destruyo el conjunto
    while((_itConj.HaySiguiente()))
    {
        _itConj.EliminarSiguiente();

    }

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
/*
void ArbolCategorias::ItHijos::copiarPos(ItHijos otroIt){

}
*/
const Conj<ArbolCategorias::DatosCat*>::Iterador ArbolCategorias::ItHijos::dameIt() const{
    return _itConj;
}

bool ArbolCategorias::ItHijos::operator==(const ItHijos& otro) const
{
    bool iguales = true;
    iguales = _itConj == otro.dameIt();
    if(iguales)
    {
        iguales = _tamanio == otro.tamanio();
    }
    /*
    bool iguales = false;
    if(tamanio() == otro.tamanio())
    {
        iguales = true;
        ItHijos itThis;
        ItHijos itOtro;
        itThis.copiarPos(*this);
        itOtro.copiarPos(otro);
        while(itThis.HaySiguiente() && iguales)
        {
            iguales = itThis.Siguiente() == itOtro.Siguiente();
            itThis.Avanzar();
            itOtro.Avanzar();

        }
    }
    else
    {
        iguales = false;
    }*/
    return iguales;
}
