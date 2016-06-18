/* 
 * File:   NodoArbolPuntoOptimo.h
 * Author: Monty
 *
 * Created on 24 de mayo de 2016, 00:03
 */

#ifndef NODOARBOLPUNTOOPTIMO_H
#define NODOARBOLPUNTOOPTIMO_H

#include "iNodoArbolPuntoOptimo.h"
#include "../../../Memoria/Object/Headers/Object.h"

class NodoArbolPuntoOptimoNodoHoja: public iNodoArbolPuntoOptimoNodoHoja, public Object
{
	private:
		size_t tamanioTablaRegistros;
		size_t cantidadRegistros;
		iRegistroPtr *tablaRegistros;

	public:
		NodoArbolPuntoOptimoNodoHoja(iRegistroPtr *listaRegistros, size_t cantidadRegistros);

		virtual iNodoArbolPuntoOptimo *Copiar();
		virtual iNodoArbolPuntoOptimo *Clone();
		virtual void Dispose();

		virtual eTipoArbol ObtenerTipoArbol();

		virtual eNodoArbolPuntoOptimo ObtenerTipoNodo();

		virtual size_t ObtenerCantidadRegistros();
		virtual iRegistroPtr ObtenerRegistro(size_t pos);

		virtual void AgregarRegistro(iRegistroPtr reg);
		virtual iRegistroPtr QuitarRegistro(size_t pos);
		virtual iRegistroPtr QuitarRegistro();

	private:
		void RedimensionarTabla(size_t nuevoTamanio);

	protected:
		virtual ~NodoArbolPuntoOptimoNodoHoja();
};

class NodoArbolPuntoOptimoNodoInterno: public iNodoArbolPuntoOptimoNodoInterno, public Object
{
	private:
		iFeaturePtr pivote;
		float radio;
		
		size_t hijoIzquierdo;
		size_t hijoDerecho;
		// El compilador protesta si hereda, por "ambiguo" >:(
		iNodoArbolPuntoOptimoNodoHojaPtr nodoHoja;

		virtual ~NodoArbolPuntoOptimoNodoInterno();
	public:
		NodoArbolPuntoOptimoNodoInterno(iRegistroPtr *listaRegistros, size_t cantidadRegistros);

		virtual iNodoArbolPuntoOptimo *Copiar();
		virtual iNodoArbolPuntoOptimo *Clone();
		virtual void Dispose();
		virtual eTipoArbol ObtenerTipoArbol();
		// Se reescribe el metodo, para mostrar el tipo correcto de nodo
		virtual eNodoArbolPuntoOptimo ObtenerTipoNodo();

		virtual iFeaturePtr ObtenerPivote();
		virtual void EstablecerPivote(iFeaturePtr pivote);
		
		virtual float ObtenerRadio();
		virtual void EstablecerRadio(float radio);

		virtual void EstablecerHijoIzquierdo(size_t nodo);
		virtual size_t ObtenerHijoIzquierdo();
		virtual void EstablecerHijoDerecho(size_t nodo);
		virtual size_t ObtenerHijoDerecho();

		virtual size_t ObtenerCantidadRegistros();
		virtual iRegistroPtr ObtenerRegistro(size_t pos);

		virtual void AgregarRegistro(iRegistroPtr reg);
		virtual iRegistroPtr QuitarRegistro(size_t pos);
		virtual iRegistroPtr QuitarRegistro();

};

#endif /* NODOARBOLPUNTOOPTIMO_H */
