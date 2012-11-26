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
    return _catDLink;
}

LinkLinkIt::ItAcceso LinkLinkIt::DatosLink::dameAccesos(){
    return _accesosRecientes;
}


int LinkLinkIt::DatosLink::dameCantAccesos(){
    return _cantAccesosRecientes;
}


Fecha LinkLinkIt::Acceso::dameDia(){
    return _dia;
}

int LinkLinkIt::Acceso::dameCantA(){
    return _cantAccesos;
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
	return _listaLinks;
}

Categoria LinkLinkIt::categoriaLink(Link link) const{
	//return _linkInfo.Obtener(link)._catDLink; HAY QUE MODIFICAR EL .H DE DICCTRIE PARA Q DEVUELVA DATOSLINK O VER CMO HACER
	return "categoriaEj";
}

Fecha LinkLinkIt::fechaUltimoAcceso(Link link){
	 //return _linkInfo.Obtener(link).dameAccesos().ultimo().dameDia(); HAY QUE CAMBIAR EL DICCIONARIO O VER COMO SE
	 // HACE, SE PUEDE HACER UN CICLO POR LA LISTA DE LOS LINKS Y LISTO, IMPORTA LA COMPLEJIDAD ACA?
	return 0;
}

int LinkLinkIt::accesosRecientesDia(Link link, Fecha fecha){
	ItAcceso itA; //como se crea el iterador?
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

void LinkLinkIt::iniciarLli(ArbolCategorias acat) const{
/*   _actual = 1;
   _acat = acat;
   int c = 1;
   _listaLinks = _listaLinks();
   _linkInfo = _linkInfo();
   COMO SE CREA EL ARREGLO ACA???
   */
}

void LinkLinkIt::nuevoLinkLli(Link link, Categoria categoria){
    /*ArbolCategorias::DatosCat* cat = this->dameAcatLli().obtenerAC(categoria);
    Lista<Acceso> accesoDeNuevoLink = Lista<Acceso>();
    DatosLink nuevoLink = <link,cat,accesoDeNuevoLink,0>;
    *DatosLink puntLink = &nuevoLink;
    _linkInfo.Definir(link,puntLink);
    _listaLinks.AgregarComoSiguiente(nuevoLink);
    while(¬(cat == NULL))
    {
        //aca iria lo de agregar el link en el arreglo
        cat = cat.damePadre();
    }

    Tira que hay parasito ja, seguramente falta el new y tambien modificar el diccionario para el definir
    */
}

void LinkLinkIt::accederLli(Link link, Fecha fecha){
    /*if (_actual == fecha){
        _actual = fecha;
    }
    DatosLink* puntLink = _linkInfo.Obtener(link);
    if(fecha == (*puntLink).dameAccesos().Ultimo().dameDia())
    {
        (*puntLink).dameAccesos().Ultimo()._cantAccesos++;
    }
    else
    {
        Acceso tuplaAcceso = <fecha, 1>
        (*puntLink).dameAccesos().AgregarComoSiguiente(tuplaAcceso);
    }
    (* puntLink)._cantAccesosRecientes++;

    PARA ESTE FALTARIA ARMAR DOS OPERACIONES DE ACCESO QUE TE DEJE MODIFICAR CANTACCESOSRECIENTES Y CANTACCESOS YA QUE COMO
    SON PRIVADAS TIRA ERROR
    */
}


int LinkLinkIt::cantLinks(Categoria categoria){
    int i = 0;
    while(_listaLinks.HaySiguiente())
    {

        i++;
        _listaLinks.Avanzar();
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

/*LinkLinkIt::itLinks::~itLinks()
    {

    }
*/

bool LinkLinkIt::itLinks::HaySiguiente() const
{
    return _itLista.HaySiguiente();
}

LinkLinkIt::DatosLink& LinkLinkIt::itLinks::Siguiente() const
{
    // DatosCat *dc = _itLista.Siguiente();

    DatosLink *res = new DatosLink();
    return *res;
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
//    _itLista.AgregarComoSiguiente(elem);
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



LinkLinkIt::itLinks::itLinks(const typename Lista<DatosLink>::Iterador& otro){

}
//iterador de acceso

/*LinkLinkIt::itAcceso::itAcceso()
{

}
*/

/*LinkLinkIt::ItAcceso::~ItAcceso()
{

}
*/

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


