#include "ArbolCategorias.h"

ArbolCategorias::ArbolCategorias(){
	_cantidad = 0;
	_alturaMax = 0;
}

ArbolCategorias::ArbolCategorias(const Categoria& raiz){
	_cantidad = 1;
	_alturaMax = 1;
	DatosCat* dato = new DatosCat();
	dato->_id = 1;
	dato->_categoria = raiz;
	dato->_altura = 1;
	//dato->_hijos = Conj<Categoria>::Conj();
	dato->_abuelo = dato;
}

//Falta el constructor por copia, el constructor por defecto(tal vez) y el destructor

Conj<Categoria> ArbolCategorias::categorias(){
	Conj<Categoria> res;
	return res;
}

Categoria ArbolCategorias::raiz(){
	return "categoriaDePrueba";
}

Categoria ArbolCategorias::padre(Categoria h){
	return "categoriaDePrueba";
}

int ArbolCategorias::id(Categoria h){
	return 0;
}

void ArbolCategorias::agregar(Categoria pagregar, Categoria padre){

}

int ArbolCategorias::altura(){
	return 0;
}

bool ArbolCategorias::esta(Categoria cat){
	return true;
}

bool ArbolCategorias::esSubCategoria(Categoria buscado, Categoria predecesor){
	return true;
}

int ArbolCategorias::alturaCategoria(Categoria cat){
	return 0;
}

Conj<Categoria> ArbolCategorias::hijos(Categoria cat){
	Conj<Categoria> res = Conj<Categoria>::Conj();
	return res;
}
