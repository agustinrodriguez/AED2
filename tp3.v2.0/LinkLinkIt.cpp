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

LinkLinkIt::DatosLink::DatosLink(){

}

LinkLinkIt::DatosLink::~DatosLink(){
    //Destruyo lista de accesos
    _accesosRecientes.~Lista();
}

LinkLinkIt::DatosLink::DatosLink(Link l,Categoria cat, Lista<Acceso> la, int i){
    _link = l;
    _catDLink = cat;
    _accesosRecientes = la;
    _cantAccesosRecientes = i;

}

bool LinkLinkIt::DatosLink::operator==(DatosLink& otro) const{
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

LinkLinkIt::Acceso::Acceso(){

}

LinkLinkIt::Acceso::Acceso(Fecha f, int a){
    _dia = f;
    _cantAccesos = a;
}
LinkLinkIt::Acceso::~Acceso(){

}

bool LinkLinkIt::Acceso::operator==(const Acceso& otro) const{
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

ArbolCategorias::ItCategorias LinkLinkIt::categoriasLli(){
    return _acat->categoriasAC();
}

Fecha LinkLinkIt::fechaActual(){
	return _actual;
}


LinkLinkIt::itLinks LinkLinkIt::linksLli()
{
    return itLinks(*this);
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
    ArbolCategorias::ItFamilia familia = _acat->Familia(categoria);
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

LinkLinkIt::itPunLinks LinkLinkIt::linksOrdenadosPorAccesos(Categoria categoria) {
        int id = dameAcat().idAC(categoria);
        Fecha f = 1;
        itPunLinks itParaFecha = itPunLinks(*this,id,f);
        Fecha fecha = itParaFecha.ultFecha();
        itPunLinks itOrdSegunF = itPunLinks(*this,id,f);
        Lista<DatosLink*> listaOrdenada = Lista<DatosLink*>();
        itPunLinks itMax;

        if (!(itOrdSegunF.estaOrdenada(fecha)))
        {
            while(_arrayCatLinks[id-1].Longitud() > 0)
            {
                itMax = itPunLinks(*this,id,f);
                itMax = itMax.BuscarMax(fecha);
                listaOrdenada.AgregarAtras(itMax.Siguiente());
                itMax.EliminarSiguiente();
            }
            _arrayCatLinks.Definir(id-1, listaOrdenada);

        }

        return itPunLinks(*this,id,f);

}

bool LinkLinkIt::esReciente(Link link, Fecha fecha){

    return fecha >= fechaUltimoAcceso(link)-2 && fecha <= fechaUltimoAcceso(link);

}

int LinkLinkIt::accesosRecientes(Link l, Categoria c)
{
    int res = 0;
    int idCat = _acat->idAC(c);
    Fecha f = 1;
    itPunLinks itP = itPunLinks(*this,idCat,f);
    Fecha f1 = itP.ultFecha();
    itPunLinks itP1 = itPunLinks(*this,idCat,f1);
    while (itP1.HaySiguiente()) {
        if (itP1.SiguienteLink() == l) {
            res = itP1.SiguienteCantidadAccesosDelLink();
        }
        itP1.Avanzar();
    }
    return res;
}

//////////////////////////////////////////
//iteradores operaciones
//////////////////////////////////////////

LinkLinkIt::itLinks::itLinks(){

}

LinkLinkIt::itLinks::itLinks(LinkLinkIt& lli){
        _itLista = lli._listaLinks.CrearIt();
}

LinkLinkIt::itLinks::itLinks(const itLinks& otroIt){
    _itLista = otroIt._itLista;
}

LinkLinkIt::itLinks::~itLinks()
    {

    }


bool LinkLinkIt::itLinks::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

Link LinkLinkIt::itLinks::Siguiente() const
{
    return _itLista.Siguiente()._link;
}

void LinkLinkIt::itLinks::Avanzar()
{
    _itLista.Avanzar();
}

bool LinkLinkIt::itLinks::operator==(const itLinks& otro) const
{
    return _itLista == otro._itLista;
}

//iterador de acceso

LinkLinkIt::ItAcceso::ItAcceso()
{

}


LinkLinkIt::ItAcceso::ItAcceso(Lista<Acceso> &ac)
{
    _itLista = ac.CrearIt();
}


LinkLinkIt::ItAcceso::ItAcceso(const ItAcceso &otroIt)
{
    _itLista = otroIt._itLista;
}

LinkLinkIt::ItAcceso::~ItAcceso()
{
    //Destruyo lista
    while(_itLista.HaySiguiente())
    {
        _itLista.EliminarSiguiente();
    }
}

bool LinkLinkIt::ItAcceso::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

LinkLinkIt::Acceso& LinkLinkIt::ItAcceso::Siguiente() const
{
    return _itLista.Siguiente();
}

void LinkLinkIt::ItAcceso::Avanzar()
{
    _itLista.Avanzar();
}

bool LinkLinkIt::ItAcceso::operator==(const ItAcceso& otro) const
{
    return _itLista == otro._itLista;
}

LinkLinkIt::itPunLinks::itPunLinks(){

}

LinkLinkIt::itPunLinks::itPunLinks(const itPunLinks &otroIt){
    _itLista = otroIt._itLista;
}

LinkLinkIt::itPunLinks::itPunLinks(LinkLinkIt& lli,int id,Fecha f){
    _itLista = lli._arrayCatLinks[id-1].CrearIt();
    _fecha = f;
}

LinkLinkIt::itPunLinks::~itPunLinks()
{

}

bool LinkLinkIt::itPunLinks::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

LinkLinkIt::DatosLink* LinkLinkIt::itPunLinks::Siguiente() const
{
 return _itLista.Siguiente();
}

Link& LinkLinkIt::itPunLinks::SiguienteLink() const{

    return _itLista.Siguiente()->_link;
}

void LinkLinkIt::itPunLinks::Avanzar()
{
    _itLista.Avanzar();
}

void LinkLinkIt::itPunLinks::EliminarSiguiente()
{
    _itLista.EliminarSiguiente();
}


LinkLinkIt::itPunLinks LinkLinkIt::itPunLinks::BuscarMax(Fecha f){
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

Fecha LinkLinkIt::itPunLinks::ultFecha(){
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

int LinkLinkIt::itPunLinks::cantAccesosDesde(Fecha f){
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
bool LinkLinkIt::itPunLinks::estaOrdenada(Fecha fecha){
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

Categoria& LinkLinkIt::itPunLinks::SiguienteCat() const{
    return Siguiente()->_catDLink;
}

int LinkLinkIt::itPunLinks::SiguienteCantidadAccesosDelLink(){
        return cantAccesosDesde(_fecha);
}

bool LinkLinkIt::itPunLinks::operator==(const itPunLinks& otro) const
{
    return _itLista == otro._itLista;
}

//bool LinkLinkIt::operator==(const LinkLinkIt& otro) const{
//    bool res = true;
//    //ARBOL DISTINTO
//    if(!(_acat == otro._acat)){
//        res = false;
//    }
//    //FECHA ACTUAL DISTINTA
//    if(_actual != otro._actual){
//        res = false;
//    }
//    //LINK DISTINTOS
//    Lista<DatosLink> links1 = _listaLinks;
//    Lista<DatosLink> links2 = otro._listaLinks;
//    itLinks itThis = itLinks(*this);
//    bool salgo = false;
//    if(links1.Longitud() == links2.Longitud())
//    {
//        while (itThis.HaySiguiente() && res){
//            itLinks itOtro = itLinks(links2);
//            salgo = false;
//            while(itOtro.HaySiguiente() && !salgo)
//            {
//                if(itThis.Siguiente() == itOtro.Siguiente())
//                {
//                    if(*_linkInfo.Obtener(itThis.Siguiente()) == *_linkInfo.Obtener(itOtro.Siguiente()) )
//                    {
//                        salgo = true;
//                    }
//                }
//                itOtro.Avanzar();
//            }
//            itThis.Avanzar();
//        }
//    }
//    else
//    {
//        res = false;
//    }
//    //Mismo arreglo
//    Fecha f =1;
//    if(_arrayCatLinks.Tamanho() == otro._arrayCatLinks.Tamanho())
//    {
//        Nat c = 0;
//        while(c < _arrayCatLinks.Tamanho() && res)
//        {
//            Lista<DatosLink*> ldl = _arrayCatLinks[c];
//            Lista<DatosLink*> ldlOtro = otro._arrayCatLinks[c];
//            itPunLinks itL = itPunLinks(ldl, f);
//            itPunLinks itLOtro = itPunLinks(ldlOtro, f);
//            while(itL.HaySiguiente() && itLOtro.HaySiguiente() && res)
//            {
//                if(!(*itL.Siguiente() == *itLOtro.Siguiente()))
//                {
//                    res = false;
//                }
//                itL.Avanzar();
//                itLOtro.Avanzar();
//            }
//            c++;
//        }
//
//    }
//    else
//    {
//        res = false;
//    }
//
//    return res;
//}
//
//
