#ifndef ARBOLCATEGORAS_H_
#define ARBOLCATEGORAS_H_

#include "aed2.h"
#include "DiccTrie.h"
#include "Tipos.h"

namespace aed2
{
	class ArbolCategorias{
		public:
		ArbolCategorias();
		ArbolCategorias(const Categoria& raiz);
		Conj<Categoria> categorias();
		Categoria raiz();
		Categoria padre(Categoria h);
		int id(Categoria h);
		void agregar(Categoria pagregar, Categoria padre);
		int altura();
		bool esta(Categoria cat);
		bool esSubCategoria(Categoria buscado, Categoria predecesor);
		int alturaCategoria(Categoria cat);
		Conj<Categoria> hijos(Categoria cat);

		struct DatosCat{
			string _categoria;
			int _id;
			int _altura;
			Conj<DatosCat*> _hijos;
			DatosCat* _abuelo;
		};

		private:

		const DatosCat* _raiz;
		int _cantidad;
		int _alturaMax;
		DiccTrie<DatosCat*> _familia;
		Lista<DatosCat> _categorias;

	};
}

#endif /* ARBOLCATEGORAS_H_ */
