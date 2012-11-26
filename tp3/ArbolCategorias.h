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
		ArbolCategorias(const ArbolCategorias& arbol);
		~ArbolCategorias();
        class DatosCat;
        class itCategorias;

        class ItCategorias{
            public:
                ItCategorias();
                ItCategorias(Lista<DatosCat> ldc);
                ~ItCategorias();
                bool HaySiguiente() const;
                Categoria Siguiente() const;
                void Avanzar();
                int tamanio() const;
                bool operator==(const ItCategorias& otro) const;
            private:
                Lista<DatosCat>::Iterador _itLista;
                int _tamanio;
        };

        class ItHijos{
            public:
                ItHijos();
                ItHijos(Conj<DatosCat*> cdc);
                ~ItHijos();
                bool HaySiguiente() const;
                Categoria Siguiente() const;
                void Avanzar();
                int tamanio() const;
                bool operator==(const ItHijos& otro) const;
            private:
                Conj<DatosCat*>::Iterador _itConj;
                int _tamanio;
        };

        class DatosCat{
            public:
                DatosCat() {};
                ~DatosCat() {};
                const Categoria& dameCat() const;
                int dameId() const;
                int dameAltura() const;
                ItHijos&  dameHijos() const;
                const DatosCat& damePadre() const;
                void agregarCat(String c);
                void agregarId(int i);
                void agregarHijos(Conj<DatosCat*> h);
                void agregarPadre(DatosCat* p);
                void agregarAltura(int a);

                //Deberias poner esto como privado, te modifique de lugar las operaciones porq sino no te deja usar la privda de la clase
                Categoria _categoria;
                int _id;
                int _altura;
                Conj<DatosCat*> _hijos;
                DatosCat* _padre;
        };


        DatosCat* obtenerAC(const Categoria c) const;
		ItCategorias categoriasAC() const;
		const Categoria& raizAC() const;
		int idAC(const Categoria& c) const;
        int alturaCatAC(const Categoria c) const;
        ItHijos& hijosAC(const Categoria& c) const;
        Categoria padreAC(const Categoria& c) const;
        int alturaAC() const;
        void agregarAC(const Categoria c, const Categoria cpadre);
        bool esta(const Categoria c) const;
		bool esSubCategoria(const Categoria c, const Categoria predecesor) const;

		private:

		const DatosCat* _raiz;
		int _cantidad;
		int _alturaMax;
		DiccTrie<DatosCat*> _familia;
		Lista<DatosCat> _categorias;
	};
}

#endif /* ARBOLCATEGORAS_H_ */
