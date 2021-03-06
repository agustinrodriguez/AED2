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
	_categorias = Lista<DatosCat*>();
	_categorias.AgregarAtras(dato);
	_familia.Definir(raiz, dato);
}
/*ArbolCategorias::ArbolCategorias(const ArbolCategorias& arbol)
{

}*/

ArbolCategorias::~ArbolCategorias()
{
    Lista<DatosCat*>::Iterador l = _categorias.CrearIt();

    while (l.HaySiguiente()) {
        delete l.Siguiente();
        l.Avanzar();
    }
}

ArbolCategorias::DatosCat::DatosCat()
{

}

ArbolCategorias::DatosCat::DatosCat(const DatosCat& otro){
    _categoria = otro._categoria;
    _id = otro._id;
    _altura = otro._altura;
    _padre = otro._padre;
    _hijos = otro._hijos;
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

ArbolCategorias::ItHijos ArbolCategorias::DatosCat::dameHijos()
{
    return ItHijos(_hijos);
}
ArbolCategorias::DatosCat* ArbolCategorias::DatosCat::damePadre() const
{
    return _padre;
}

void ArbolCategorias::DatosCat::agregarHijo(DatosCat* h){
    _hijos.Agregar(h);

}

bool ArbolCategorias::DatosCat::operator==(const DatosCat& otro) const{
    bool altura = _altura == otro._altura;
    bool cat = _categoria == otro._categoria;
    bool id = _id == otro._id;
    bool hijos = true;
    bool padre = true;
    Conj<DatosCat*> conj1 = _hijos;
    Conj<DatosCat*> conj2 = otro._hijos;
    ItHijos hijos1 = ItHijos(conj1);
    ItHijos hijos2 = ItHijos(conj2);
    while(hijos1.HaySiguiente() && hijos){
        if(!(hijos2.definido(hijos1.Siguiente()))){
            hijos = false;
        }
        hijos1.Avanzar();
    }
    if(_padre!=NULL && otro._padre!=NULL){
        padre = _padre->dameCat() == otro._padre->dameCat();
    }
    else{
        padre = _padre == NULL && otro._padre == NULL;
    }
    return altura && cat && id && hijos && padre;
}

bool ArbolCategorias::ItHijos::definido(Categoria cat) const{
    bool res = false;
    ItHijos hijos = *this;
    while(hijos.HaySiguiente() && !res){
        if(hijos.Siguiente() == cat){
            res = true;
        }
        hijos.Avanzar();
    }
    return res;
}

ArbolCategorias::DatosCat* ArbolCategorias::obtenerAC(const Categoria c) const
{
    return _familia.Obtener(c);
}

ArbolCategorias::ItCategorias ArbolCategorias::categoriasAC()
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

ArbolCategorias::ItHijos ArbolCategorias::hijosAC(const Categoria& c)
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
    _cantidad++;
    Conj<DatosCat*> hijos = Conj<DatosCat*>();
    DatosCat *tuplaA = new DatosCat(c, _cantidad, puntPadre->dameAltura()+1, hijos, puntPadre);
    puntPadre->agregarHijo(tuplaA);
    _familia.Definir(c, tuplaA);
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
            DatosCat* actual = _familia.Obtener(predecesor)->damePadre();
            DatosCat* puntC = _familia.Obtener(c);
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

const int ArbolCategorias::dameCantidad() const
{
    return _cantidad;
}

ArbolCategorias::ItCategorias::ItCategorias()
{

}

ArbolCategorias::ItCategorias::ItCategorias(Lista<DatosCat*>& ldc)
{
    _itLista = ldc.CrearIt();
}

ArbolCategorias::ItCategorias::ItCategorias(const ItCategorias& otroIt){
    _itLista = otroIt._itLista;
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
    return _itLista.Siguiente()->dameCat();
}

void ArbolCategorias::ItCategorias::Avanzar()
{
    _itLista.Avanzar();
}

bool ArbolCategorias::ItCategorias::operator==(const ItCategorias& otro) const
{
    return _itLista == otro._itLista;
}

ArbolCategorias::ItHijos::ItHijos()
{

}

ArbolCategorias::ItHijos::ItHijos(const ArbolCategorias::ItHijos &otroIt)
{
    _itConj= otroIt._itConj;
}

ArbolCategorias::ItHijos::ItHijos(Conj<DatosCat*> &cdc)
{
    _itConj = cdc.CrearIt();
}

ArbolCategorias::ItHijos::~ItHijos()
{

}

bool ArbolCategorias::ItHijos::HaySiguiente() const
{
    return _itConj.HaySiguiente();
}

const Categoria& ArbolCategorias::ItHijos::Siguiente() const
{
    return _itConj.Siguiente()->dameCat();
}

void ArbolCategorias::ItHijos::Avanzar()
{
    _itConj.Avanzar();
}

bool ArbolCategorias::ItHijos::operator==(const ItHijos& otro) const
{
    return _itConj == otro._itConj;
}
bool ArbolCategorias::operator==(const ArbolCategorias& acat) const{
    bool raiz = (*_raiz == *acat._raiz);
    bool cantidad = (_cantidad == acat._cantidad);
    bool altura = (_alturaMax == acat._alturaMax);
    Lista<DatosCat*> listaCat1 = _categorias;
    Lista<DatosCat*> listaCat2 = acat._categorias;
    ItCategorias categorias1 = ItCategorias(listaCat1);
    ItCategorias categorias2 = ItCategorias(listaCat2);
    bool categorias = true;
    bool mismoDicc = true;
    while(categorias1.HaySiguiente() && categorias2.HaySiguiente() && categorias && mismoDicc){
        categorias = (categorias1.Siguiente() == categorias2.Siguiente());
        if(categorias){
        mismoDicc = (*acat._familia.Obtener(categorias2.Siguiente()) == *_familia.Obtener(categorias1.Siguiente()));
        }
        categorias1.Avanzar();
        categorias2.Avanzar();
    }
    return raiz && cantidad && altura && categorias && mismoDicc;
}
