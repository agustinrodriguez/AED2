#include "LinkLinkIt.h"
#include "ArbolCategorias.h"


LinkLinkIt::LinkLinkIt(ArbolCategorias* acat)
{
    _actual = 1;
    _acat = acat;
    _arrayCatLinks = Arreglo<Lista<DatosLink*> >(_acat->dameCantidad());
    _listaLinks = Lista<DatosLink>();

    int c = 0;
    while ( c < _acat->dameCantidad() ) {
        Lista<DatosLink*> list = Lista<DatosLink*>();
        _arrayCatLinks.Definir(c, list);
        c++;
    }
}

LinkLinkIt::~LinkLinkIt()
{
    Lista<DatosLink>::Iterador l = _listaLinks.CrearIt();

    while (l.HaySiguiente()) {
        delete _linkInfo.Obtener(l.Siguiente()._link);
        l.Avanzar();
    }
}

DatosLink::DatosLink(){

}

DatosLink::~DatosLink(){
    //Destruyo lista de accesos
    _accesosRecientes.~Lista();
}

DatosLink::DatosLink(Link l,Categoria cat, Lista<Acceso> la, int i){
    _link = l;
    _catDLink = cat;
    _accesosRecientes = la;
    _cantAccesosRecientes = i;

}

bool DatosLink::operator==(DatosLink& otro) const{
    bool res = true;
    res = _link == otro._link;
    if (res) {
        res = _accesosRecientes == otro._accesosRecientes;
        if (res) {
            res = _cantAccesosRecientes == otro._cantAccesosRecientes;
            if (res) {
                res = _catDLink == otro._catDLink;
            }
        }
    }
    return res;
}

Acceso::Acceso(){

}

Acceso::Acceso(Fecha f, int a){
    _dia = f;
    _cantAccesos = a;
}
Acceso::~Acceso(){

}

bool Acceso::operator==(const Acceso& otro) const{
    bool iguales = true;
    iguales = _dia == otro._dia;
    if(iguales)
    {
        iguales = _cantAccesos == otro._cantAccesos;
    }
    return iguales;
}

ArbolCategorias& LinkLinkIt::dameAcat() const{
	return *_acat;
}

ItCategorias LinkLinkIt::categoriasLli(){
    return _acat->categoriasAC();
}

Fecha LinkLinkIt::fechaActual(){
	return _actual;
}


itLinks LinkLinkIt::linksLli()
{
    return CrearItLinks();
}

Categoria LinkLinkIt::categoriaLink(Link link) const
{
	return _linkInfo.Obtener(link)->_catDLink;
}

Fecha LinkLinkIt::fechaUltimoAcceso(Link link)
{
	return _linkInfo.Obtener(link)->_accesosRecientes.Ultimo()._dia;
}

int LinkLinkIt::accesosRecientesDia(Link link, Fecha fecha)
{
    Lista<Acceso> la = _linkInfo.Obtener(link)->_accesosRecientes;
	ItAcceso itA = ItAcceso(la);
	int res = 0;
	while (itA.HaySiguiente()) {
	    if(itA.Siguiente()._dia == fecha) {
	        res = itA.Siguiente()._cantAccesos;
	    }
	    itA.Avanzar();
	}
	return res;
}

void LinkLinkIt::iniciarLli(ArbolCategorias *acat) {
   _actual = 1;
   _acat = acat;
   int c = 0;
   DiccTrie<DatosLink*> _linkInfo = DiccTrie<DatosLink*>();
    _arrayCatLinks = Arreglo<Lista<DatosLink*> >(_acat->dameCantidad());
    _listaLinks = Lista<DatosLink>();
    _linkInfo = DiccTrie<DatosLink*>();
    while(c <= _acat->dameCantidad())
   {
        Lista<DatosLink*> list = Lista<DatosLink*>();
        _arrayCatLinks.Definir(c, list);
        c++;
   }

}

void LinkLinkIt::nuevoLinkLli(Link link, Categoria categoria){
 	Lista<Acceso> accesoDeNuevoLink = Lista<Acceso>();
    DatosLink* puntLink = new DatosLink(link, categoria, accesoDeNuevoLink, 0);
    _linkInfo.Definir(link, puntLink);
    _listaLinks.AgregarAtras(*puntLink);
    ArbolCategorias::ItFamilia familia = _acat->CrearItFamilia(categoria);
    while(familia.HaySiguiente())
    {
        _arrayCatLinks[familia.SiguienteId() - 1].AgregarAtras(puntLink);
        familia.Avanzar();
    }

}

void LinkLinkIt::accederLli(Link link, Fecha fecha){
    if (_actual != fecha) {
        _actual = fecha;
    }
    DatosLink* puntLink = _linkInfo.Obtener(link);
    if (!puntLink->_accesosRecientes.EsVacia() && fecha == puntLink->_accesosRecientes.Ultimo()._dia) {
        puntLink->_accesosRecientes.Ultimo()._cantAccesos++;
    } else {
        Acceso nuevoAcceso = Acceso(fecha, 1);
        puntLink->_accesosRecientes.AgregarAtras(nuevoAcceso);
    }
    if (puntLink->_accesosRecientes.Longitud() == 4) {
        puntLink->_cantAccesosRecientes = puntLink->_cantAccesosRecientes - puntLink->_accesosRecientes.Primero()._cantAccesos;
        puntLink->_accesosRecientes.Fin();
    }

    puntLink->_cantAccesosRecientes++;

}


int LinkLinkIt::cantLinks(Categoria categoria){
    	return _arrayCatLinks[_acat->idAC(categoria)-1].Longitud();
}

itPunLinks LinkLinkIt::linksOrdenadosPorAccesos(Categoria categoria) {
        int id = dameAcat().idAC(categoria);
        Fecha n = 1;
        itPunLinks itParaFecha = itPunLinks(_arrayCatLinks[id-1], n);
        Fecha fecha = itParaFecha.ultFecha();
        itPunLinks itOrdSegunF = itPunLinks(_arrayCatLinks[id-1], fecha);
        Lista<DatosLink*> listaOrdenada = Lista<DatosLink*>();
        itPunLinks itMax;

        if (!(itOrdSegunF.estaOrdenada(fecha)))
        {
            while(_arrayCatLinks[id-1].Longitud() > 0)
            {
                itMax = itPunLinks(_arrayCatLinks[id-1], fecha);
                itMax = itMax.BuscarMax(fecha);
                listaOrdenada.AgregarAtras(itMax.Siguiente());
                itMax.EliminarSiguiente();
            }
            _arrayCatLinks.Definir(id-1, listaOrdenada);

        }

       return itPunLinks(_arrayCatLinks[id-1], fecha);

}

bool LinkLinkIt::esReciente(Link link, Fecha fecha){

return fecha >= fechaUltimoAcceso(link)-2 && fecha <= fechaUltimoAcceso(link);
}

itLinks LinkLinkIt::CrearItLinks(){
    return itLinks(_listaLinks);
}



//////////////////////////////////////////
//iteradores operaciones
//////////////////////////////////////////

itLinks::itLinks(){

}

itLinks::itLinks(Lista<DatosLink>& ldl){
        _itLista = ldl.CrearIt();
}

itLinks::itLinks(const itLinks& otroIt){
    _itLista = otroIt._itLista;
}

itLinks::~itLinks()
    {

    }


bool itLinks::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

Link itLinks::Siguiente() const
{
    return _itLista.Siguiente()._link;
}

void itLinks::Avanzar()
{
    _itLista.Avanzar();
}

bool itLinks::operator==(const itLinks& otro) const
{
    return _itLista == otro._itLista;
}

//iterador de acceso

ItAcceso::ItAcceso()
{

}


ItAcceso::ItAcceso(Lista<Acceso> &ac)
{
    _itLista = ac.CrearIt();
}


ItAcceso::ItAcceso(const ItAcceso &otroIt)
{
    _itLista = otroIt._itLista;
}

ItAcceso::~ItAcceso()
{
    //Destruyo lista
    while(_itLista.HaySiguiente())
    {
        _itLista.EliminarSiguiente();
    }
}

bool ItAcceso::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

Acceso& ItAcceso::Siguiente() const
{
    return _itLista.Siguiente();
}

void ItAcceso::Avanzar()
{
    _itLista.Avanzar();
}

bool ItAcceso::operator==(const ItAcceso& otro) const
{
    return _itLista == otro._itLista;
}

itPunLinks::itPunLinks(){

}

itPunLinks::itPunLinks(const itPunLinks &otroIt){
    _itLista = otroIt._itLista;
}

itPunLinks::itPunLinks(Lista<DatosLink*> &ldl, Fecha& f){
    _itLista = ldl.CrearIt();
    _fecha = f;
}

itPunLinks::~itPunLinks()
{

}

bool itPunLinks::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

DatosLink* itPunLinks::Siguiente() const
{
 return _itLista.Siguiente();
}

Link& itPunLinks::SiguienteLink() const{

    return _itLista.Siguiente()->_link;
}

void itPunLinks::Avanzar()
{
    _itLista.Avanzar();
}

void itPunLinks::EliminarSiguiente()
{
    _itLista.EliminarSiguiente();
}


itPunLinks itPunLinks::BuscarMax(Fecha f){
     itPunLinks res = itPunLinks(*this);
    while(HaySiguiente())
    {
        if(cantAccesosDesde(f) > res.cantAccesosDesde(f))
        {
            res = itPunLinks(*this);
        }
        Avanzar();
    }
    return res;
}

Fecha itPunLinks::ultFecha(){
    int res = 0;
    if (!Siguiente()->_accesosRecientes.EsVacia()) {
        res = Siguiente()->_accesosRecientes.Ultimo()._dia;
    }

    while(HaySiguiente())
    {
        if(!Siguiente()->_accesosRecientes.EsVacia() && res < Siguiente()->_accesosRecientes.Ultimo()._dia){
            res = Siguiente()->_accesosRecientes.Ultimo()._dia;
        }
        Avanzar();
    }
    return res;
}

int itPunLinks::cantAccesosDesde(Fecha f){
    Lista<Acceso> lA = Siguiente()->_accesosRecientes;
    ItAcceso itAcc = ItAcceso(lA);
    int res = 0;
    while(itAcc.HaySiguiente())
    {

        if(itAcc.Siguiente()._dia <= f && itAcc.Siguiente()._dia >= f -2)
        {
            res = res + itAcc.Siguiente()._cantAccesos;
        }
        itAcc.Avanzar();
    }
    return res;
}
bool itPunLinks::estaOrdenada(Fecha fecha){
    bool res = true;
    int aux = cantAccesosDesde(fecha);
    Avanzar();
    while (HaySiguiente()) {
        if (cantAccesosDesde(fecha) > aux) {
            res = false;
        }
        aux = cantAccesosDesde(fecha);
        Avanzar();
    }
    return res;
}

Categoria& itPunLinks::SiguienteCat() const{
    return Siguiente()->_catDLink;
}

int itPunLinks::SiguienteCantidadAccesosDelLink(){
        return cantAccesosDesde(_fecha);
}

bool itPunLinks::operator==(const itPunLinks& otro) const
{
    return _itLista == otro._itLista;
}

bool LinkLinkIt::operator==(const LinkLinkIt& otro) const{
    bool res = true;
    //ARBOL DISTINTO
    if(!(_acat == otro._acat)){
        res = false;
    }
    //FECHA ACTUAL DISTINTA
    if(_actual != otro._actual){
        res = false;
    }
    //LINK DISTINTOS
    Lista<DatosLink> links1 = _listaLinks;
    Lista<DatosLink> links2 = otro._listaLinks;
    itLinks itThis = itLinks(links1);
    bool salgo = false;
    Fecha f;
    if(links1.Longitud() == links2.Longitud())
    {
        while (itThis.HaySiguiente() && res){
            itLinks itOtro = itLinks(links2);
            salgo = false;
            while(itOtro.HaySiguiente() && !salgo)
            {
                if(itThis.Siguiente() == itOtro.Siguiente())
                {
                    if(*_linkInfo.Obtener(itThis.Siguiente()) == *_linkInfo.Obtener(itOtro.Siguiente()) )
                    {
                        salgo = true;
                    }
                }
                itOtro.Avanzar();
            }
            itThis.Avanzar();
        }
    }
    else
    {
        res = false;
    }
    //Mismo arreglo
    if(_arrayCatLinks.Tamanho() == otro._arrayCatLinks.Tamanho())
    {
        Nat c = 0;
        while(c < _arrayCatLinks.Tamanho() && res)
        {
            Lista<DatosLink*> ldl = _arrayCatLinks[c];
            Lista<DatosLink*> ldlOtro = otro._arrayCatLinks[c];
            itPunLinks itL = itPunLinks(ldl, f);
            itPunLinks itLOtro = itPunLinks(ldlOtro, f);
            while(itL.HaySiguiente() && itLOtro.HaySiguiente() && res)
            {
                if(!(*itL.Siguiente() == *itLOtro.Siguiente()))
                {
                    res = false;
                }
                itL.Avanzar();
                itLOtro.Avanzar();
            }
            c++;
        }

    }
    else
    {
        res = false;
    }

    return res;
}


