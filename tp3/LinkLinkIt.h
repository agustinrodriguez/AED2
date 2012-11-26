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
                Acceso() {};
                ~Acceso() {};
                Fecha dameDia();
                int dameCantA();
                void guardoAcceso(int a);
                void guardoDia(int a);

        private:
			Fecha _dia;
			int _cantAccesos;

	};

	class ItAcceso
        {
        public:
            ItAcceso();
            ItAcceso(Lista<Acceso> ac) ;
                ~ItAcceso() ;
                bool HaySiguiente() const;
                Acceso& Siguiente() const;
                void Avanzar();
                void EliminarSiguiente();
                void AgregarComoSiguiente(const Acceso& elem);
                Acceso Ultimo();
                bool operator==(const ItAcceso& otro) const;
            private:
                Lista<Acceso>::Iterador _itLista;
                int _tamanio;
        };



        class DatosLink{
		public:
            DatosLink() {};
            ~DatosLink() {};
            Link dameLink() const;
            ArbolCategorias::DatosCat dameCatDLink();
            Lista<Acceso> dameAccesos();
            int dameCantAccesos();
            void nuevoLink(String l);
            void nuevaCat(ArbolCategorias::DatosCat* c);
            void nuevoAccesos(Lista<Acceso> ita);
            void nuevoCantAccesosRecientes(int car);
        private:
			Link _link;
			ArbolCategorias::DatosCat* _catDLink;
			Lista<Acceso> _accesosRecientes;
			int _cantAccesosRecientes;

			};

//creacion de la clase iterador de datoslink
        class itLinks
        {
        public:
            itLinks();
            itLinks(Lista<DatosLink> ldl);
                ~itLinks();
                bool HaySiguiente() const;
                DatosLink& Siguiente() const;
                void Avanzar();
                void EliminarSiguiente();
                void AgregarComoSiguiente(const DatosLink& elem);
                itLinks BuscarMax(Fecha f);
                Fecha ultFecha();
                int cantAccesosDesde(Fecha f);
                bool estaOrdenada();
                //itLinks(const Lista<DatosLink>::Iterador& otro);
                bool operator==(const itLinks& otro) const;
            private:
                Lista<DatosLink>::Iterador _itLista;
                int _tamanio;
        };

        LinkLinkIt(ArbolCategorias arbolito);
        LinkLinkIt();
        ~LinkLinkIt();

        ArbolCategorias dameAcatLli() const;
        ArbolCategorias::ItCategorias categoriasLli();
		Fecha fechaActual();
		itLinks linksLli() const;
		Categoria categoriaLink(Link link) const;
		Fecha fechaUltimoAcceso(Link link);
		int accesosRecientesDia(Link link, Fecha fecha);
		void iniciarLli(ArbolCategorias acat);
		void nuevoLinkLli(Link link, Categoria categoria);
		void accederLli(Link link, Fecha fecha);
		int cantLinks(Categoria categoria);
		itLinks linksOrdenadosPorAccesos(Categoria categoria) const;

        private:

		ArbolCategorias _acat;
		Fecha _actual;
		DiccTrie<DatosLink*> _linkInfo;
		Lista<DatosLink> _listaLinks;
		Arreglo<Lista<DatosLink*> > _arrayCatLinks;

	};
}

#endif /* LINKLINKIT */
