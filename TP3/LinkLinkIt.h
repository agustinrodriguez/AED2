#ifndef LINKLINKIT_H_
#define LINKLINKIT_H_

#include "aed2.h"
#include "ArbolCategorias.h"
#include "DiccTrie.h"

namespace aed2
{
	class LinkLinkIt{
		public:

		LinkLinkIt(ArbolCategorias arbolito);
		ArbolCategorias categorias();
		Conj<Link> links();
		Categoria categoriaLink(Link link);
		Fecha fechaActual();
		Fecha fechaUltimoAcceso(Link link);
		int accesosRecientesDia(Link link, Fecha fecha);
		void nuevoLink(Link link, Categoria categoria);
		void acceso(Link link, Fecha fecha);
		bool esReciente(Link link, Fecha fecha);
		int accesosRecientes(Link link);
		//Lista<Link> linksOrdenadosPorAccesos();
		int cantLinks(Categoria categoria);
		Fecha menorReciente(Link link);
		Fecha diasRecientes(Link link);
		Fecha diasRecientesDesde(Link link);//Es igual a la anterior?
		Conj<Fecha> diasRecientesParaCategoria(Categoria categoria);
		Link linkConUltimoAcceso(Categoria categoria, Conj<Link> conjunto);
		int sumarAccesosRecientes(Link link, Conj<Fecha> conjunto);
		//buscarMax
		//bool estaOrdenada(Lista<DatosLink*>);

		private:

		struct Acceso{
			Fecha _dia;
			int _cantAccesos;
		};

		struct DatosLink{
			Link _link;
			ArbolCategorias::DatosCat* _catDLink;
			Lista<Acceso> _accesosRecientes;
			int _cantAccesosRecientes;
		};

		struct LinksFamilia{
			Lista<DatosLink*> _lfamilia;
		};
		
		ArbolCategorias _acat;
		Fecha _actual;
		DiccTrie<DatosLink*> _accesosXLink;
		Lista<DatosLink> _listaLinks;

	};
}

#endif /* LINKLINKIT */
