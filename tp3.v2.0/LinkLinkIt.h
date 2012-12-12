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
                    itLinks(LinkLinkIt& lli);
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

            class itPuntLinks {
                public:

                    itPuntLinks();
                    itPuntLinks(LinkLinkIt& lli,int id, Fecha& f);
                    itPuntLinks(const itPuntLinks& otroIt);
                    ~itPuntLinks();
                    bool HaySiguiente() const;
                    Link& SiguienteLink();
                    Categoria& SiguienteCategoria();
                    int SiguienteCantAccesos();
                    void Avanzar();
                    void EliminarSiguiente();
                    itPuntLinks BuscarMax(Fecha f);
                    Fecha ultFecha();
                    int cantAccesosDesde(Fecha f);
                    bool estaOrdenada(Fecha f);
                    bool operator==(const itPuntLinks& otro) const;
                    friend class LinkLinkIt;

                private:
                    Lista<DatosLink*>::Iterador _itLista;
                    Fecha _fecha;
                    DatosLink* SiguienteDL() const;
            };

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
            itPuntLinks linksOrdenadosPorAccesos(Categoria categoria) ;
            bool esReciente(Link link, Fecha fecha);
            int accesosRecientes(Link l, Categoria c);
            bool operator==(const LinkLinkIt& otro) const;
	};
}

#endif /* LINKLINKIT */
