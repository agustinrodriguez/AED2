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
	//return (*(_linkInfo.Obtener(link)))._catDLink;
	return "hola";
}

Fecha LinkLinkIt::fechaUltimoAcceso(Link link){
	return 0;
}

int LinkLinkIt::accesosRecientesDia(Link link, Fecha fecha){
	return 0;
}

LinkLinkIt LinkLinkIt::iniciarLli(ArbolCategorias acat) const{
   return LinkLinkIt(acat);
}

void LinkLinkIt::nuevoLinkLli(Link link, Categoria categoria){

}

void LinkLinkIt::accederLli(Link link, Fecha fecha){

}


int LinkLinkIt::cantLinks(Categoria categoria){
	return 0;
}

LinkLinkIt::itLinks LinkLinkIt::linksOrdenadosPorAccesos(Categoria categoria) const{
    itLinks itL;
    return itL;
}

bool LinkLinkIt::esReciente(Link link, Fecha fecha){
	return true;
}

int LinkLinkIt::accesosRecientes(Link link){
	return 0;
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


