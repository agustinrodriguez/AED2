#ifndef DICCTRIE_H
#define DICCTRIE_H
#include "aed2.h"
#include <string>

#define TAMANIO 256

using namespace std;

template <class T>
class DiccTrie
{
  public:
	DiccTrie();
	~DiccTrie();
	void Definir(const String& c, T& s);
	bool Def(const String& c) const;
	T& Obtener(const String& c) const;

  private:
	struct Nodo {
		T valor;
		bool valido;
		Nodo* elems[TAMANIO];

		Nodo() : valido(false){
			for (int i = 0; i < TAMANIO; i++){
				elems[i] = NULL;
			}
		}

		~Nodo() {
			for (int i = 0; i < TAMANIO;i++){
				if(elems[i] != NULL) {
					delete elems[i];
					elems[i] = NULL;
				}
			}
		}
	};

	Nodo* raiz;
};


template<class T>
DiccTrie<T>::DiccTrie(){
	raiz = new Nodo;
}

template<class T>
DiccTrie<T>::~DiccTrie(){
	delete raiz;
	raiz = NULL;
}

template<class T>
void DiccTrie<T>::Definir(const String& c, T& s){
	Nodo* nodo = raiz;
	Nodo* temp;
	string::const_iterator it = c.begin();
	while(it < c.end()){
		int i = (int)(*it);
		temp = nodo->elems[i];
		if(temp == NULL){
			temp = new Nodo;
			nodo->elems[i] = temp;
		}
		nodo = temp;
		it++;
	}
	nodo->valor = s;
	nodo->valido = true;
}

template<class T>
bool DiccTrie<T>::Def(const String& c) const{
	bool res = true;
	Nodo* nodo =raiz;
	string::const_iterator it = c.begin();
	while((it < c.end()) && (res == true)){
		int i = (int)(*it);
		res = (nodo->elems[i] != NULL);
		nodo = nodo->elems[i];
		it++;
	}
	if(res == true){
		res = (nodo->valido == true);
	}
	return res;
}

template<class T>
T& DiccTrie<T>::Obtener(const String& c) const {
		Nodo* nodo = raiz;
		string::const_iterator it = c.begin();
		while(it < c.end()){
			int i = (int)(*it);
			nodo = nodo->elems[i];
			it++;
		}
		return nodo->valor;
}

#endif
