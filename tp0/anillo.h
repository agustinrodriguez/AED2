#ifndef ANILLO_H_
#define ANILLO_H_

#include <iostream>
#include <cassert>
using namespace std;

//se puede asumir que el tipo T tiene constructor por copia
//y operator==
//no se puede asumir que el tipo T tenga operator=
template<typename T>
class Anillo {
public:

	/*
	 * constructor por defecto, crea un anillo
	 */
	Anillo();

	/*
	 * constructor por copia, una vez copiado, ambos anillos deben ser
	 * independientes, es decir, cuando se borre uno no debe morir el otro.
	 */
	Anillo(const Anillo<T>&);

	/*
	 * Destructor. Acordarse de liberar toda la memoria!
	 */
	~Anillo();

	/*
	 * Devuelve true si los anillos son iguales
	 */
	bool operator==(const Anillo<T>&) const;

	/*
	 * Dice si el anillo es vac�o.
	 */

	bool esVacio() const;

	/*
	 * Dice el tamanio del anillo
	 */
	int tamanio() const;

	/*
	 * Devuelve el elemento actual del anillo
	 * PRE: no es vac�o el anillo.
	 */
    const T& actual() const;

	/*
	 * Devuelve el pr�ximo elemento seg�n el orden del anillo.
	 * El anillo debe rotar. Con lo cual sucesivas llamadas a esta funci�n
	 * retornan distintos valores.
	 *
	 * El valor retornado pasa a ser el anterior.
	 *
	 * PRE: no es vac�o el anillo.
	 */
	const T& siguiente();

	/*
	 * Agrega el elemento al anillo. Recordar que el �ltimo agregado es el
	 * actual
	 */
	void agregar(const T&);

	/*
	 * Elimina una ocurrencia del elemento en el anillo.
	 */
	void eliminar(const T&);

	/*
	 * Marca el elemento actual.
	 *
	 * PRE: no es vac�o el anillo.
	 */
    void marcar();

	/*
	 * Indica si alg�n del anillo est� marcado.
	 */
	bool hayMarcado() const;

	/*
	 * Indica cu�l es el elemento marcado la �ltima vez.
	 *
	 * PRE: hayMarcado
	 */
    const T& marcado() const;

	/*
	 * Vuelve hacia atr�s un elemento.
	 * El anterior, en caso de existir, no debe alterarse.
	 */
	void retroceder();

	/*
	 * debe mostrar el anillo en el stream (y retornar el mismo).
	 * Anillo vacio: []
	 * Anillo con 2 elementos (e1 es el actual): [e1, e2]
	 * Anillo con 2 elementos (e2 es el actual y e1 fue marcado): [e2, e1*]
	 * Anillo con 3 elementos (e3 es el actual, e2 fue agregado antes que e3, e1 fue agregado antes que e2): [e3, e2, e1]
	 *
	 */
	ostream& mostrarAnillo(ostream&) const;

private:
	//No se puede modificar esta funcion.
	Anillo<T>& operator=(const Anillo<T>& otro) {
		assert(false);
		return *this;
	}

	//Aca va la implementacion del nodo.
	struct Nodo {
	    Nodo * siguiente;
	    Nodo * anterior;
	    T * valor;
        Nodo() {
            valor = NULL;
            siguiente = NULL;
            anterior = NULL;
        };
        ~Nodo() {
            delete valor;
        };
	};

	int _longitud;
    Nodo * _actual;
    T * _marcado;
};

template<class T>
ostream& operator<<(ostream& out, const Anillo<T>& a) {
	return a.mostrarAnillo(out);
}

// implementaci�n a hacer por los alumnos
template<class T>
Anillo<T>::Anillo()
{
    _longitud = 0;
    _actual = NULL;
    _marcado = NULL;
}

template<class T>
Anillo<T>::~Anillo()
{
    _marcado = NULL;
    int i = 0;
    while(i<_longitud){
        if (_longitud-1 == i){
            delete _actual;
            _actual = NULL;
        }else {
            Nodo* temp = _actual;
            _actual = (*_actual).siguiente;
            delete temp;
        }
        i++;
    }
}

template<class T>
bool Anillo<T>::operator==(const Anillo<T>& anillo) const
{
    Nodo * thisAnilloNodo = _actual;
    Nodo * otroAnilloNodo = anillo._actual;
    int i = 0;
    bool iguales = tamanio() == anillo.tamanio();

    while (i<_longitud && iguales) {
        iguales = *((*thisAnilloNodo).valor) == *((*otroAnilloNodo).valor);
        if (hayMarcado() && thisAnilloNodo->valor == _marcado) {
            iguales = iguales && anillo.hayMarcado() && otroAnilloNodo->valor == anillo._marcado;
        }

        thisAnilloNodo = (*thisAnilloNodo).siguiente;
        otroAnilloNodo = (*otroAnilloNodo).siguiente;
        i++;
    }

    return iguales;
}

template<class T>
bool Anillo<T>::esVacio() const
{
    return _longitud == 0;
}

template<class T>
int Anillo<T>::tamanio() const
{
    return _longitud;
}
template<class T>
Anillo<T>::Anillo(const Anillo<T>& anillo)
{
    _longitud = 0;
    _marcado = NULL;

    if(!anillo.esVacio()){
        int i = 0;
        Nodo * _elementoEnLugar = (*anillo._actual).anterior;
        for(i=0; i<anillo.tamanio(); i++){
            agregar(*(*_elementoEnLugar).valor);
            if (anillo.hayMarcado() && (*_elementoEnLugar).valor == anillo._marcado) marcar();
            _elementoEnLugar = (*_elementoEnLugar).anterior;
        }
    }else{
        _actual = NULL;
    }
}

template<class T>
const T& Anillo<T>::actual() const
{
    return *((*_actual).valor);
}

template<class T>
const T& Anillo<T>::siguiente()
{
    _actual = (*_actual).siguiente;

    return *((*_actual).valor);
}

template<class T>
void Anillo<T>::agregar(const T& e)
{
    Nodo * nuevoNodo = new Nodo;
    (*nuevoNodo).valor =  new T(e);
    if (esVacio()) {
        (*nuevoNodo).siguiente = nuevoNodo;
        (*nuevoNodo).anterior = nuevoNodo;
    } else {
        (*nuevoNodo).siguiente = _actual;
        (*nuevoNodo).anterior = (*_actual).anterior;
        (*(*_actual).anterior).siguiente = nuevoNodo;
        (*_actual).anterior = nuevoNodo;
    }

    _actual = nuevoNodo;
    _longitud++;
}

template<class T>
void Anillo<T>::eliminar(const T& e)
{
    if (!esVacio()) {
        bool founded = false;
        int i = 0;
        Nodo * recorroActual = _actual;

        while (i < _longitud && !founded) {
            if ( *((*recorroActual).valor) == e ) {
                founded = true;
                (*(*recorroActual).anterior).siguiente = (*recorroActual).siguiente;
                (*(*recorroActual).siguiente).anterior = (*recorroActual).anterior;
                _longitud--;
                if (esVacio()) {
                    delete _actual;
                    _actual = NULL;
                } else {
                    Nodo * nodoTemp = recorroActual;
                    if ((*recorroActual).valor == (*_actual).valor) {
                        _actual = (*_actual).siguiente;
                    }
                    if ((*recorroActual).valor == _marcado) {
                        _marcado = NULL;
                    }
                    delete nodoTemp;
                }

            } else {
                recorroActual = (*recorroActual).siguiente;
            }
            i++;
        }
    }
}

template<class T>
void Anillo<T>::marcar()
{
    if (!esVacio()) _marcado = (*_actual).valor;
}

template<class T>
bool Anillo<T>::hayMarcado() const
{
    return _marcado != NULL;
}

template<class T>
const T& Anillo<T>::marcado() const
{
    return (*_marcado);
}

template<class T>
void Anillo<T>::retroceder()
{
    if(!esVacio()){
        _actual = (*_actual).anterior;
    }

}

template<class T>
ostream& Anillo<T>::mostrarAnillo(ostream& os) const
{
    os << "[";
    Nodo * loQueSeMuestra = _actual;
    int i = 0;
    while (i<_longitud)
    {
        if (i != 0) {
            os << ", ";
        }
        os << *((*loQueSeMuestra).valor);
        if (hayMarcado() && _marcado == (*loQueSeMuestra).valor) {
            os << "*";
        }
        loQueSeMuestra = (*loQueSeMuestra).siguiente;

        i++;
    }
    os << "]";

    return os;
}


#endif //ANILLO_H_
