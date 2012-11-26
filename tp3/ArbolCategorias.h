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
        class DatosCat{
            public:
                DatosCat() {};
                ~DatosCat() {};

                Categoria _categoria;
                int _id;
                int _altura;
                Conj<DatosCat*> _hijos;
                DatosCat* _padre;
        };

        class ItCategorias{
            public:
                ItCategorias();
                ~ItCategorias();
                bool HaySiguiente() const;
                Categoria& Siguiente() const;
                void Avanzar();
                void EliminarSiguiente();
                void AgregarComoSiguiente(const Categoria& elem);

                bool operator==(const ItCategorias& otro) const;
            private:
                Lista<DatosCat>::Iterador _itLista;
                // deberia poder acceder a la misma propiedad categorias, de ArbolDeCategorias (que es lo q va a iterar)
                // creo que es como una propiedad amiga, habria q ver como ellos lo hicieron
        };

        const Categoria& dameCat(const DatosCat& dc) const;
        int dameId(const DatosCat& dc) const;
        int dameAltura(const DatosCat& dc) const;
        ItCategorias& dameHijos(const DatosCat& dc) const;
        const DatosCat& damePadre(const DatosCat& dc) const;

        DatosCat* obtenerAC(const Categoria c) const;
		ItCategorias categoriasAC() const;
		const Categoria& raizAC() const;
		int idAC(const Categoria& c) const;
        int alturaCatAC(const Categoria c) const;
        ItCategorias& hijosAC(const Categoria& c) const;
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
