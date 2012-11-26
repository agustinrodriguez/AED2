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
        private:
			Fecha _dia;
			int _cantAccesos;

	};

	class ItAcceso
        {
        public:
            ItAcceso() {};
                ~ItAcceso() {};
                bool HaySiguiente() const;
                Acceso& Siguiente() const;
                void Avanzar();
                void EliminarSiguiente();
                void AgregarComoSiguiente(const Acceso& elem);

                bool operator==(const ItAcceso& otro) const;
            private:
                Lista<Acceso>::Iterador _itLista;
        };



        class DatosLink{
		public:
            DatosLink() {};
            ~DatosLink() {};
            Link dameLink() const;
            ArbolCategorias::DatosCat dameCatDLink();
            ItAcceso dameAccesos();
            int dameCantAccesos();
        private:
			Link _link;
			ArbolCategorias::DatosCat _catDLink;
			ItAcceso _accesosRecientes;
			int _cantAccesosRecientes;

			};

//creacion de la clase iterador de datoslink
        class itLinks
        {
        public:
            itLinks() {};
                ~itLinks() {};
                bool HaySiguiente() const;
                DatosLink& Siguiente() const;
                void Avanzar();
                void EliminarSiguiente();
                void AgregarComoSiguiente(const DatosLink& elem);

                bool operator==(const itLinks& otro) const;
            private:
                Lista<DatosLink>::Iterador _itLista;
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
		LinkLinkIt iniciarLli(ArbolCategorias acat) const;
		void nuevoLinkLli(Link link, Categoria categoria);
		void accederLli(Link link, Fecha fecha);
		int cantLinks(Categoria categoria);
		itLinks linksOrdenadosPorAccesos(Categoria categoria) const;
		bool esReciente(Link link, Fecha fecha);
		int accesosRecientes(Link link);

        private:

		ArbolCategorias _acat;
		Fecha _actual;
		DiccTrie<DatosLink*> _linkInfo;
		itLinks _listaLinks;

	};
}

#endif /* LINKLINKIT */
