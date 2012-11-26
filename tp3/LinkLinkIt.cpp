#include "LinkLinkIt.h"
#include "ArbolCategorias.h"


LinkLinkIt::LinkLinkIt(ArbolCategorias arbolito){

}

LinkLinkIt::~LinkLinkIt(){

}

Link LinkLinkIt::DatosLink::dameLink() const{
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
    this->_link = l;

}

void LinkLinkIt::DatosLink::nuevaCat(ArbolCategorias::DatosCat* c){
    this->_catDLink = c;
}

void LinkLinkIt::DatosLink::nuevoAccesos(Lista<Acceso> ita){
    this->_accesosRecientes = ita;

}

void LinkLinkIt::DatosLink::nuevoCantAccesosRecientes(int car){
    this->_cantAccesosRecientes = car;

}

Fecha LinkLinkIt::Acceso::dameDia(){
    return _dia;
}

int LinkLinkIt::Acceso::dameCantA(){
    return _cantAccesos;
}

void LinkLinkIt::Acceso::guardoAcceso(int a){
    this->_cantAccesos = a;
}

void LinkLinkIt::Acceso::guardoDia(int a){
    this->_dia = a;
}

ArbolCategorias LinkLinkIt::dameAcatLli() const{
	return _acat;
}

ArbolCategorias::ItCategorias LinkLinkIt::categoriasLli(){
    return _acat.categoriasAC();
}

Fecha LinkLinkIt::fechaActual(){
	return _actual;
}

LinkLinkIt::itLinks LinkLinkIt::linksLli() const{
itLinks res = new itLinks(_listaLinks);
 	return res;
}

Categoria LinkLinkIt::categoriaLink(Link link) const{
	return _linkInfo.Obtener(link)->dameCatDLink().dameCat();
}

Fecha LinkLinkIt::fechaUltimoAcceso(Link link){
//	 return _linkInfo.Obtener(link)->dameAccesos().ultimo().dameDia();
    return 0;
}

int LinkLinkIt::accesosRecientesDia(Link link, Fecha fecha){
	ItAcceso itA = ItAcceso(_linkInfo.Obtener(link)->dameAccesos());
	int res;
	while(itA.HaySiguiente())
	{
	    if(itA.Siguiente().dameDia() == fecha)
	    {
	        res = itA.Siguiente().dameCantA();
	    }
	    itA.Avanzar();
	}
	return res;
}

void LinkLinkIt::iniciarLli(ArbolCategorias acat) {
   _actual = 1;
   _acat = acat;
   itLinks _listaLinks = itLinks();
   DiccTrie<DatosLink*> _linkInfo = DiccTrie<DatosLink*>();
    Arreglo<itLinks> _arrayCatLinks = Arreglo<itLinks>((acat.categoriasAC().tamanio()));
   while(acat.categoriasAC().HaySiguiente())
   {
       /*itLinks itL = itLinks();
        _arrayCatLinks.Definir(acat.categoriasAC.HaySiguiente()->dameId,itL);
        acat.categoriasAC().HaySiguiente
      // c++;*/
   }

}

void LinkLinkIt::nuevoLinkLli(Link link, Categoria categoria){
    ArbolCategorias::DatosCat* cat = this->dameAcatLli().obtenerAC(categoria);
    Lista<Acceso> accesoDeNuevoLink;
    DatosLink nuevoLink;
    nuevoLink.nuevoLink(link);
    nuevoLink.nuevaCat(cat);
    nuevoLink.nuevoAccesos(accesoDeNuevoLink);
    nuevoLink.nuevoCantAccesosRecientes(0);
//    _linkInfo.Definir(link*, nuevoLink*);
//    _listaLinks.AgregarComoSiguiente(nuevoLink);
    while(!(cat == NULL))
    {
        itLinks itL;
//        _arrayCatLinks.[cat->dameId()]
        *cat = cat->damePadre();
    }

}

void LinkLinkIt::accederLli(Link link, Fecha fecha){
    if (_actual == fecha){
        _actual = fecha;
    }
    DatosLink* puntLink = _linkInfo.Obtener(link);
    if(fecha == puntLink->dameAccesos().Ultimo().dameDia())
    {
        int a = puntLink->dameAccesos().Ultimo().dameCantA();
        a++;
        puntLink->dameAccesos().Ultimo().guardoAcceso(a);
    }
    else
    {
        Acceso nuevoAcceso;
        nuevoAcceso.guardoDia(fecha);
        nuevoAcceso.guardoAcceso(1);
//        puntLink->dameAccesos().AgregarComoSiguiente(nuevoAcceso);
    }

    int b = puntLink->dameCantAccesos();
    b++;
    puntLink->nuevoCantAccesosRecientes(b);

}


int LinkLinkIt::cantLinks(Categoria categoria){
    int i = 0;
//    while(_listaLinks.HaySiguiente())
    {

        i++;
//        _listaLinks.Avanzar();
    }
	return i;
}

LinkLinkIt::itLinks LinkLinkIt::linksOrdenadosPorAccesos(Categoria categoria) const{
    itLinks itL;
    return itL;
}

//////////////////////////////////////////
//iteradores operaciones
//////////////////////////////////////////

LinkLinkIt::itLinks::itLinks(){

}

LinkLinkIt::itLinks::itLinks(Lista<DatosLink> ldl){
       _itLista = ldl.CrearIt();
        _tamanio = ldl.Longitud();


}


LinkLinkIt::itLinks::~itLinks()
    {

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

}


bool LinkLinkIt::itLinks::operator==(const itLinks& otro) const
{
    return false;
}

LinkLinkIt::itLinks LinkLinkIt::itLinks::BuscarMax(Fecha f){
    itLinks res;
    while(this->HaySiguiente())
    {
        if(this->cantAccesosDesde(f) > res.cantAccesosDesde(f))
        {
            //res.itLinks(this); VER COMO SE COPIA EL ITERADOR
        }
        this->Avanzar();
    }
    return res;
}

Fecha LinkLinkIt::itLinks::ultFecha(){
    int res = this->Siguiente().dameAccesos().Ultimo().dameDia();
    while(this->HaySiguiente())
    {
        if(res < this->Siguiente().dameAccesos().Ultimo().dameDia()){
            res = this->Siguiente().dameAccesos().Ultimo().dameDia();
        }
        this->Avanzar();
    }
    return res;
}

int LinkLinkIt::itLinks::cantAccesosDesde(Fecha f){
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
bool LinkLinkIt::itLinks::estaOrdenada(){
    return false;
}


//iterador de acceso

LinkLinkIt::ItAcceso::ItAcceso()
{

}


LinkLinkIt::ItAcceso::ItAcceso(Lista<Acceso> ac)
{
    _itLista = ac.CrearIt();
    _tamanio = ac.Longitud();

}


LinkLinkIt::ItAcceso::~ItAcceso()
{

}


bool LinkLinkIt::ItAcceso::HaySiguiente() const
{
    return false;
}

LinkLinkIt::Acceso& LinkLinkIt::ItAcceso::Siguiente() const
{
    Acceso *res = new Acceso();
    return *res;
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
//    _itLista.AgregarComoSiguiente(elem);
}


bool LinkLinkIt::ItAcceso::operator==(const ItAcceso& otro) const
{
    return false;
}

LinkLinkIt::Acceso LinkLinkIt::ItAcceso::Ultimo(){
    Acceso ac;
    return ac;
}


