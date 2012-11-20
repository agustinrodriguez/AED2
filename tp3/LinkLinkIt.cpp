#include "LinkLinkIt.h"
#include "ArbolCategorias.h"

LinkLinkIt::LinkLinkIt(ArbolCategorias arbolito){
	
}

ArbolCategorias LinkLinkIt::categorias(){
	ArbolCategorias ab = ArbolCategorias("CategoriaDePrueba");
	return ab;
}

Conj<Link> LinkLinkIt::links(){
	Conj<Link> links = Conj<Link>::Conj();
	return links;
}

Categoria LinkLinkIt::categoriaLink(Link link){
	return "CategoriaDePrueba";
}

Fecha LinkLinkIt::fechaActual(){
	return 0;
}

Fecha LinkLinkIt::fechaUltimoAcceso(Link link){
	return 0;
}

int LinkLinkIt::accesosRecientesDia(Link link, Fecha fecha){
	return 0;
}

void LinkLinkIt::nuevoLink(Link link, Categoria categoria){

}

void LinkLinkIt::acceso(Link link, Fecha fecha){

}

bool LinkLinkIt::esReciente(Link link, Fecha fecha){
	return true;
}

int LinkLinkIt::accesosRecientes(Link link){
	return 0;
}

//Lista<Link> LinkLinkIt::linksOrdenadosPorAccesos(){
//
//}

int LinkLinkIt::cantLinks(Categoria categoria){
	return 0;
}

Fecha LinkLinkIt::menorReciente(Link link){
	return 0;
}

Fecha LinkLinkIt::diasRecientes(Link link){
	return 0;
}

Fecha LinkLinkIt::diasRecientesDesde(Link link){
	return 0;
}

Conj<Fecha> LinkLinkIt::diasRecientesParaCategoria(Categoria categoria){
	Conj<Fecha> fechas = Conj<Fecha>::Conj();
	return fechas;
}

Link LinkLinkIt::linkConUltimoAcceso(Categoria categoria, Conj<Link> conjunto){
	return "LinkDePrueba";
}

int LinkLinkIt::sumarAccesosRecientes(Link link, Conj<Fecha> conjunto){
	return 0;
}

//buscarMax

//bool LinkLinkIt::estaOrdenada(Lista<DatosLink*>){
//	return true;
//}
