#ifndef LINKLINKIT_H_
#define LINKLINKIT_H_

#include "aed2.h"
#include "ArbolCategorias.h"
#include "DiccTrie.h"
//#include "datosLink.cpp"

namespace aed2
{
	class LinkLinkIt{
		public:
            class Acceso{
                public:
                    Acceso();
                    Acceso(Fecha f, int a);
                    ~Acceso() ;
                    Fecha dameDia() const;
                    int dameCantA() const;
                    void guardoAcceso(int a);
                    void guardoDia(int a);
                    bool operator==(const Acceso& otro) const;

                private:
                    Fecha _dia;
                    int _cantAccesos;

            };

            class ItAcceso{
                public:
                    ItAcceso();
                    ItAcceso(Lista<Acceso> &ac) ;
                    ItAcceso(const ItAcceso &otroIt);
                        ~ItAcceso() ;
                        bool HaySiguiente() const;
                        Acceso& Siguiente() const;
                        void Avanzar();
                        bool operator==(const ItAcceso& otro) const;
                    private:
                        Lista<Acceso>::Iterador _itLista;
            };

            class DatosLink {
                public:
                    DatosLink();
                    DatosLink(Link l, ArbolCategorias::DatosCat* dc, Lista<Acceso> la, int i);
                    ~DatosLink();
                    const Link& dameLink() const;
                    ArbolCategorias::DatosCat dameCatDLink();
                    Lista<Acceso> dameAccesos();
                    int dameCantAccesos();
                    void nuevoLink(String l);
                    void nuevaCat(ArbolCategorias::DatosCat* c);
                    void agregarAcceso(Acceso acceso);
                    void nuevoAccesos(Lista<Acceso> ita);
                    void nuevoCantAccesosRecientes(int car);
                    bool operator==(DatosLink& otro) const;

                private:
                    Link _link;
                    ArbolCategorias::DatosCat* _catDLink;
                    Lista<Acceso> _accesosRecientes;
                    int _cantAccesosRecientes;
            };

            //creacion de la clase iterador de datoslink
            class itLinks {
                public:
                    itLinks(Lista<DatosLink>& ldl);
                    itLinks();
                    ~itLinks();
                    itLinks(const itLinks& otroIt);
                    bool HaySiguiente() const;
                    Link Siguiente() const;
                    void Avanzar();
                    bool operator==(const itLinks& otro) const;
                private:
                    Lista<DatosLink>::Iterador _itLista;
                    Lista<DatosLink> _lista;
            };

            //creacion de la clase iterador de puntero a datoslink
            class itPunLinks {
                public:
                    itPunLinks();
                    itPunLinks(Lista<DatosLink*>& ldl, Fecha& f);
                    itPunLinks(const itPunLinks& otroIt);
                    ~itPunLinks();
                    bool HaySiguiente() const;
                    DatosLink* Siguiente() const;
                    Link SiguienteLink() const;
                    Categoria SiguienteCat() const;
                    int SiguienteCantidadAccesosDelLink();
                    void Avanzar();
                    void EliminarSiguiente();
                    itPunLinks BuscarMax(Fecha f);
                    Fecha ultFecha();
                    int cantAccesosDesde(Fecha f);
                    bool estaOrdenada(Fecha f);
                    bool operator==(const itPunLinks& otro) const;
                private:
                    Lista<DatosLink*>::Iterador _itLista;
                    Fecha _fecha;
                    Categoria _cat;

            };

            LinkLinkIt(ArbolCategorias *acat);
            LinkLinkIt();
            ~LinkLinkIt();

            ArbolCategorias dameAcatLli() const;
            ArbolCategorias::ItCategorias categoriasLli();
            Fecha fechaActual();
            itLinks linksLli();
            Categoria categoriaLink(Link link) const;
            Fecha fechaUltimoAcceso(Link link);
            int accesosRecientesDia(Link link, Fecha fecha);
            void iniciarLli(ArbolCategorias *acat);
            void nuevoLinkLli(Link link, Categoria categoria);
            void accederLli(Link link, Fecha fecha);
            int cantLinks(Categoria categoria);
            itPunLinks linksOrdenadosPorAccesos(Categoria categoria) ;

        private:
            ArbolCategorias* _acat;
            Fecha _actual;
            DiccTrie<DatosLink*> _linkInfo;
            Lista<DatosLink> _listaLinks;
            Arreglo<Lista<DatosLink*> > _arrayCatLinks;
	};
}

#endif /* LINKLINKIT */
