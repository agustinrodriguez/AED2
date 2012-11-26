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

        class DatosCat{
            public:
                DatosCat() {};
                ~DatosCat() {};
                const Categoria& dameCat() const;
                int dameId() const;
                int dameAltura() const;
                ItCategorias&  dameHijos() const;
                const DatosCat& damePadre() const;
                void agregarCat(String c);
                void agregarId(int i);
                void agregarHijos(ItCategorias h);
                void agregarPadre(DatosCat* p);
                void agregarAltura(int a);

                //Deberias poner esto como privado, te modifique de lugar las operaciones porq sino no te deja usar la privda de la clase
                Categoria _categoria;
                int _id;
                int _altura;
                ItCategorias _hijos;
                DatosCat* _padre;
        };


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
		ItCategorias _categorias;
	};
}

#endif /* ARBOLCATEGORAS_H_ */
