#ifndef ARBOLCATEGORAS_H_
#define ARBOLCATEGORAS_H_

#include "aed2.h"
#include "DiccTrie.h"
#include "Tipos.h"

namespace aed2
{
	class ArbolCategorias{
		private:
            class DatosCat{
                public:
                    ~DatosCat();
                    DatosCat();
                    DatosCat(const DatosCat& otro);
                    DatosCat(const Categoria cat, int id, int altura, Conj<DatosCat*> hijos, DatosCat* padre);
                    void copiarDc(DatosCat otroDc);
                    bool operator==(const DatosCat& otro) const;
                private:
                    Categoria _categoria;
                    int _id;
                    int _altura;
                    Conj<DatosCat*> _hijos;
                    DatosCat* _padre;
                    friend class ArbolCategorias;
            };
            DatosCat* _raiz;
            int _cantidad;
            int _alturaMax;
            DiccTrie<DatosCat*> _familia;
            Lista<DatosCat*> _categorias;

		public:
            ArbolCategorias();
            ArbolCategorias(const Categoria& raiz);
            ~ArbolCategorias();

            class ItFamilia{
                public:
                ItFamilia(DatosCat* cat);
                bool HaySiguiente() const;
                void Avanzar();
                const Categoria& SiguienteCat() const;
                int SiguienteId() const;

                private:
                DatosCat* _elDatoC;
            };

            class ItCategorias{
                public:
                    ~ItCategorias();
                    bool HaySiguiente() const;
                    Categoria Siguiente() const;
                    void Avanzar();
                    friend class ArbolCategorias;
                    friend class LinkLinkIt;

                private:
                    Lista<DatosCat*>::Iterador _itLista;
                    ItCategorias();
                    ItCategorias(Lista<DatosCat*> &ldc);
                    ItCategorias(const ItCategorias &otroIt);
                    bool operator==(const ItCategorias& otro) const;

            };

            class ItHijos{
                public:
                    ~ItHijos();
                    ItHijos();
                    ItHijos(Conj<DatosCat*> &cdc);
                    ItHijos(const ItHijos &otroIt);
                    bool HaySiguiente() const;
                    const Categoria& Siguiente() const;
                    void Avanzar();
                    friend class DatosCat;
                    friend class ArbolCategorias;
                private:
                    Conj<DatosCat*>::Iterador _itConj;
                    bool operator==(const ItHijos& otro) const;
                    bool definido(Categoria cat) const;

            };

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
            ItFamilia CrearItFamilia(const Categoria &c);
            ItCategorias CrearItCategorias();
            ItHijos CrearItHijos(const Categoria &c);

	};
}

#endif /* ARBOLCATEGORAS_H_ */
