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
		/*ArbolCategorias(const ArbolCategorias& arbol);*/
		~ArbolCategorias();
        class DatosCat;
        class itCategorias;

        class ItCategorias{
            public:
                ItCategorias();
                ItCategorias(Lista<DatosCat*> &ldc);
                ItCategorias(const ItCategorias &otroIt);
                ~ItCategorias();
                bool HaySiguiente() const;
                Categoria Siguiente() const;
                void Avanzar();
                bool operator==(const ItCategorias& otro) const;
            private:
                Lista<DatosCat*>::Iterador _itLista;
        };

        class ItHijos{
            public:
                ItHijos();
                ItHijos(Conj<DatosCat*> &cdc);
                ItHijos(const ItHijos &otroIt);
                ~ItHijos();
                bool HaySiguiente() const;
                const Categoria& Siguiente() const;
                void Avanzar();
                bool operator==(const ItHijos& otro) const;
                bool definido(Categoria cat) const;
            private:
                Conj<DatosCat*>::Iterador _itConj;

        };

        class DatosCat{
            public:
                DatosCat();
                DatosCat(const DatosCat& otro);
                DatosCat(const Categoria cat, int id, int altura, Conj<DatosCat*> hijos, DatosCat* padre);
                ~DatosCat();
                const Categoria& dameCat() const;
                int dameId() const;
                int dameAltura() const;
                ItHijos dameHijos();
                DatosCat* damePadre() const;
                void agregarHijo(DatosCat* h);
                void copiarDc(DatosCat otroDc);
                bool operator==(const DatosCat& otro) const;

            private:
                Categoria _categoria;
                int _id;
                int _altura;
                Conj<DatosCat*> _hijos;
                DatosCat* _padre;
        };


        DatosCat* obtenerAC(const Categoria c) const;
		ItCategorias categoriasAC();
		const Categoria& raizAC() const;
		int idAC(const Categoria& c) const;
        int alturaCatAC(const Categoria c) const;
        ItHijos hijosAC(const Categoria& c);
        Categoria padreAC(const Categoria& c) const;
        int alturaAC() const;
        void agregarAC(const Categoria c, const Categoria cpadre);
        bool esta(const Categoria c) const;
		bool esSubCategoria(const Categoria c, const Categoria predecesor) const;
        const int dameCantidad() const;
        bool operator==(const ArbolCategorias& acat) const;

		private:

		DatosCat* _raiz;
		int _cantidad;
		int _alturaMax;
		DiccTrie<DatosCat*> _familia;
		Lista<DatosCat*> _categorias;
	};
}

#endif /* ARBOLCATEGORAS_H_ */
