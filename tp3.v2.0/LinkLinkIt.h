#ifndef LINKLINKIT_H_
#define LINKLINKIT_H_

#include "aed2.h"
#include "ArbolCategorias.h"
#include "DiccTrie.h"

namespace aed2
{
    class LinkLinkIt{
        private:
            class Acceso {
                public:
                    ~Acceso() ;
                    Acceso();
                    Acceso(Fecha f, int a);
                    bool operator==(const Acceso& otro) const;
                private:
                    Fecha _dia;
                    int _cantAccesos;
                    friend class LinkLinkIt;
            };

            class ItAcceso {
                public:
                    ~ItAcceso();
                    ItAcceso();
                    ItAcceso(Lista<Acceso> &ac) ;
                    ItAcceso(const ItAcceso &otroIt);
                private:
                    Lista<Acceso>::Iterador _itLista;
                    bool HaySiguiente() const;
                    Acceso& Siguiente() const;
                    void Avanzar();
                    bool operator==(const ItAcceso& otro) const;
                    friend class LinkLinkIt;
            };


            class DatosLink
            {
                public:
                    ~DatosLink();
                    DatosLink();
                    DatosLink(Link l, Categoria cat, Lista<Acceso> la, int i);
                private:
                    Link _link;
                    Categoria _catDLink;
                    Lista<Acceso> _accesosRecientes;
                    int _cantAccesosRecientes;
                    void agregarAcceso(Acceso acceso);
                    void nuevoAccesos(Lista<Acceso> ita);
                    void nuevoCantAccesosRecientes(int car);
                    bool operator==(DatosLink& otro) const;
                    friend class LinkLinkIt;
            };

                //VARIABLES PRIVADAS DE LLI

            ArbolCategorias* _acat;
            Fecha _actual;
            DiccTrie<DatosLink*> _linkInfo;
            Lista<DatosLink> _listaLinks;
            Arreglo<Lista<DatosLink*> > _arrayCatLinks;

        public:
            class itLinks {
                public:
                    itLinks(Lista<DatosLink>& ldl);
                    itLinks();
                    ~itLinks();
                    itLinks(const itLinks& otroIt);
                    itLinks crearItLinks(LinkLinkIt lli) const;
                    bool HaySiguiente() const;
                    Link Siguiente() const;
                    void Avanzar();
                    bool operator==(const itLinks& otro) const;

                private:
                    Lista<DatosLink>::Iterador _itLista;
            };

            //creacion de la clase iterador de puntero a datoslink
            class itPunLinks {
                public:
                    itPunLinks();
                    itPunLinks(Lista<DatosLink*>& ldl, Fecha& f);
                    itPunLinks(const itPunLinks& otroIt);
                    ~itPunLinks();
                    bool HaySiguiente() const;
                    Link& SiguienteLink() const;
                    Categoria& SiguienteCat() const;
                    int SiguienteCantidadAccesosDelLink();
                    void Avanzar();
                    void EliminarSiguiente();
                    itPunLinks BuscarMax(Fecha f);
                    Fecha ultFecha();
                    int cantAccesosDesde(Fecha f);
                    bool estaOrdenada(Fecha f);
                    bool operator==(const itPunLinks& otro) const;
                    friend class LinkLinkIt;
                private:
                    Lista<DatosLink*>::Iterador _itLista;
                    Fecha _fecha;
                    DatosLink* Siguiente() const;
            };

            //creacion de la clase iterador de datoslink
            LinkLinkIt(ArbolCategorias *acat);
            LinkLinkIt();
            ~LinkLinkIt();

            ArbolCategorias& dameAcat() const;
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
            bool esReciente(Link link, Fecha fecha);
            bool operator==(const LinkLinkIt& otro) const;
	};
}

#endif /* LINKLINKIT */
