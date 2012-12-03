#include "LinkLinkIt.h"
#include "ArbolCategorias.h"


LinkLinkIt::LinkLinkIt(ArbolCategorias* acat)
{
    _actual = 1;
    _acat = acat;
//    _linkInfo = DiccTrie<DatosLink*>(); NO SE XQ ROMPE, PERO CREO QUE NO IMPORTA
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
        delete _linkInfo.Obtener(l.Siguiente().dameLink());
        l.Avanzar();
    }
}

LinkLinkIt::DatosLink::DatosLink(){

}

LinkLinkIt::DatosLink::~DatosLink(){
    //Destruyo catDlink
    if(_catDLink != NULL)
    {
        _catDLink = NULL;
    }
    //Destruyo lista de accesos
    _accesosRecientes.~Lista();
}

LinkLinkIt::DatosLink::DatosLink(Link l, ArbolCategorias::DatosCat* dc, Lista<Acceso> la, int i){
    _link = l;
    _catDLink = dc;
    _accesosRecientes = la;
    _cantAccesosRecientes = i;

}

const Link& LinkLinkIt::DatosLink::dameLink() const{
    return _link;
}


ArbolCategorias::DatosCat LinkLinkIt::DatosLink::dameCatDLink(){
    return *_catDLink;
}

Lista<LinkLinkIt::Acceso> LinkLinkIt::DatosLink::dameAccesos(){

    return _accesosRecientes;
}


int LinkLinkIt::DatosLink::dameCantAccesos(){
    return _cantAccesosRecientes;
}

void LinkLinkIt::DatosLink::nuevoLink(String l){
    _link = l;

}

void LinkLinkIt::DatosLink::nuevaCat(ArbolCategorias::DatosCat* c){
    _catDLink = c;
}

void LinkLinkIt::DatosLink::agregarAcceso(Acceso acceso)
{
    _accesosRecientes.AgregarAtras(acceso);
}

void LinkLinkIt::DatosLink::nuevoAccesos(Lista<Acceso> ita){
    _accesosRecientes = ita;
}

void LinkLinkIt::DatosLink::nuevoCantAccesosRecientes(int car){
    _cantAccesosRecientes = car;
}

bool LinkLinkIt::DatosLink::operator==(DatosLink& otro) const{
    bool res = true;
    res = _link == otro.dameLink();
    if (res) {
        res = _accesosRecientes == otro.dameAccesos();
        if (res) {
            res = _cantAccesosRecientes == otro.dameCantAccesos();
            if (res) {
                res = *_catDLink == otro.dameCatDLink();
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
Fecha LinkLinkIt::Acceso::dameDia() const{
    return _dia;
}

int LinkLinkIt::Acceso::dameCantA() const{
    return _cantAccesos;
}

void LinkLinkIt::Acceso::guardoAcceso(int a){
    _cantAccesos = a;
}

void LinkLinkIt::Acceso::guardoDia(int a){
    _dia = a;
}

bool LinkLinkIt::Acceso::operator==(const LinkLinkIt::Acceso& otro) const{
    bool iguales = true;
    iguales = _dia == otro.dameDia();
    if(iguales)
    {
        iguales = _cantAccesos == otro.dameCantA();
    }
    return iguales;
}

ArbolCategorias LinkLinkIt::dameAcatLli() const{
	return *_acat;
}

ArbolCategorias::ItCategorias LinkLinkIt::categoriasLli(){
    return _acat->categoriasAC();
}

Fecha LinkLinkIt::fechaActual(){
	return _actual;
}


LinkLinkIt::itLinks LinkLinkIt::linksLli() const
{
    itLinks res = itLinks(_listaLinks);
 	return res;
}

Categoria LinkLinkIt::categoriaLink(Link link) const
{
	return _linkInfo.Obtener(link)->dameCatDLink().dameCat();
}

Fecha LinkLinkIt::fechaUltimoAcceso(Link link)
{
	return _linkInfo.Obtener(link)->dameAccesos().Ultimo().dameDia();
}

int LinkLinkIt::accesosRecientesDia(Link link, Fecha fecha)
{
	ItAcceso itA = ItAcceso(_linkInfo.Obtener(link)->dameAccesos());
	int res = 0;
	while (itA.HaySiguiente()) {
	    if(itA.Siguiente().dameDia() == fecha) {
	        res = itA.Siguiente().dameCantA();
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

//    ArbolCategorias::DatosCat cat = ArbolCategorias::DatosCat(*dameAcatLli().obtenerAC(categoria));
// 	ArbolCategorias::DatosCat* puntCat = &cat;
// 	DatosLink nuevoLink = DatosLink(link, puntCat, accesoDeNuevoLink, 0);
//    DatosLink* puntLink = &nuevoLink;

    ArbolCategorias::DatosCat* puntCat = _acat->obtenerAC(categoria);

 	Lista<Acceso> accesoDeNuevoLink = Lista<Acceso>();
    DatosLink* puntLink = new DatosLink(link, puntCat, accesoDeNuevoLink, 0);

    _linkInfo.Definir(link, puntLink);
    _listaLinks.AgregarAtras(*puntLink);

    while(!(puntCat == NULL))
    {
        _arrayCatLinks[puntCat->dameId() - 1].AgregarAtras(puntLink);
        puntCat = puntCat->damePadre();
    }

}

void LinkLinkIt::accederLli(Link link, Fecha fecha){
    if (_actual != fecha) {
        _actual = fecha;
    }
    DatosLink* puntLink = _linkInfo.Obtener(link);
    int a = 0;
    if (!puntLink->dameAccesos().EsVacia() && fecha == puntLink->dameAccesos().Ultimo().dameDia()) {
        a = puntLink->dameAccesos().Ultimo().dameCantA();
        a++;
        Lista<Acceso> nuevosAccesos = puntLink->dameAccesos();
        nuevosAccesos.Ultimo().guardoAcceso(a);
        puntLink->nuevoAccesos(nuevosAccesos);
//        puntLink->dameAccesos().Ultimo().guardoAcceso(a);
    } else {
        Acceso nuevoAcceso = Acceso(fecha, 1);
        puntLink->agregarAcceso(nuevoAcceso);
//        puntLink->dameAccesos().AgregarAtras(nuevoAcceso);
    }

    puntLink->nuevoCantAccesosRecientes(puntLink->dameCantAccesos() + 1);

}


int LinkLinkIt::cantLinks(Categoria categoria){
    	return _listaLinks.Longitud();
}

LinkLinkIt::itPunLinks LinkLinkIt::linksOrdenadosPorAccesos(Categoria categoria) {
        int id = dameAcatLli().idAC(categoria);
        itPunLinks *itParaFecha = new itPunLinks(_arrayCatLinks[id]);
        Fecha fecha = itParaFecha->ultFecha();
        Lista<DatosLink*> listaOrdenada = Lista<DatosLink*>();
        if (!(itParaFecha->estaOrdenada()))
        {
            itPunLinks itMax = itPunLinks(_arrayCatLinks[id]);
            while(_arrayCatLinks[id].Longitud() != 0)
            {
                itMax = itMax.BuscarMax(fecha);
                listaOrdenada.AgregarAtras(itMax.Siguiente());
                itMax.EliminarSiguiente();
            }
            _arrayCatLinks.Definir(id,listaOrdenada);

        }

       return itPunLinks(_arrayCatLinks[id]);
       //LE SAQUE EL CONST YA QUE CON EL CONST NO PUEDO MODIFICAR _ARRAYCATLINKS HABRIA QUE HACER UNA OPERACION PARA PODER MOD
}

//////////////////////////////////////////
//iteradores operaciones
//////////////////////////////////////////

LinkLinkIt::itLinks::itLinks(){

}

LinkLinkIt::itLinks::itLinks(Lista<DatosLink> ldl){
       Lista<DatosLink> ld = Lista<DatosLink>();
       ld = ldl;
       _itLista = ldl.CrearIt();
        _lista = ld;
}

LinkLinkIt::itLinks::itLinks(const itLinks& otroIt){
    _itLista = otroIt._itLista;
}

LinkLinkIt::itLinks::~itLinks()
    {
        _lista.~Lista();
    }


bool LinkLinkIt::itLinks::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

LinkLinkIt::DatosLink& LinkLinkIt::itLinks::Siguiente() const
{
 return _itLista.Siguiente();
}

void LinkLinkIt::itLinks::Avanzar()
{
    _itLista.Avanzar();
}

void LinkLinkIt::itLinks::EliminarSiguiente()
{
    _itLista.EliminarSiguiente();
}

void LinkLinkIt::itLinks::AgregarComoSiguiente(const DatosLink& elem)
{
    _itLista.AgregarComoSiguiente(elem);
}

bool LinkLinkIt::itLinks::operator==(const itLinks& otro) const
{
    return _itLista == otro._itLista;
}

//iterador de acceso

LinkLinkIt::ItAcceso::ItAcceso()
{

}


LinkLinkIt::ItAcceso::ItAcceso(Lista<Acceso> ac)
{
    _itLista = ac.CrearIt();
}


LinkLinkIt::ItAcceso::ItAcceso(const LinkLinkIt::ItAcceso& otroIt)
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

void LinkLinkIt::ItAcceso::EliminarSiguiente()
{
    _itLista.EliminarSiguiente();
}

void LinkLinkIt::ItAcceso::AgregarComoSiguiente(const Acceso& elem)
{
    _itLista.AgregarComoSiguiente(elem);
}

bool LinkLinkIt::ItAcceso::operator==(const ItAcceso& otro) const
{
    return _itLista == otro._itLista;
}

LinkLinkIt::itPunLinks::itPunLinks(){

}

LinkLinkIt::itPunLinks::itPunLinks(const itPunLinks& otroIt){
    _itLista = otroIt._itLista;
}

LinkLinkIt::itPunLinks::itPunLinks(Lista<DatosLink*> ldl){
    _itLista = ldl.CrearIt();
}

LinkLinkIt::itPunLinks::~itPunLinks()
{
    //Destruyo lista
    _lista.~Lista();
}

bool LinkLinkIt::itPunLinks::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

LinkLinkIt::DatosLink* LinkLinkIt::itPunLinks::Siguiente() const
{
 return _itLista.Siguiente();
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
    int res = Siguiente()->dameAccesos().Ultimo().dameDia();
    while(HaySiguiente())
    {
        if(res < Siguiente()->dameAccesos().Ultimo().dameDia()){
            res = Siguiente()->dameAccesos().Ultimo().dameDia();
        }
        Avanzar();
    }
    return res;
}

int LinkLinkIt::itPunLinks::cantAccesosDesde(Fecha f){
    ItAcceso itAcc;
    int res = 0;
    while(itAcc.HaySiguiente())
    {
        if(itAcc.Siguiente().dameDia() == f)
        {
            res = res + itAcc.Siguiente().dameCantA();
        }
        itAcc.Avanzar();
    }
    return res;
}
bool LinkLinkIt::itPunLinks::estaOrdenada(){
    return false;
}

bool LinkLinkIt::itPunLinks::operator==(const itPunLinks& otro) const
{
    return _itLista == otro._itLista;
}

