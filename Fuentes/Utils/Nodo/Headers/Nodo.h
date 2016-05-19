/* 
 * File:   Nodo.h
 * Author: Monty
 *
 * Created on 25 de abril de 2016, 23:48
 */

#ifndef NODO_H
#define	NODO_H

#include "iNodo.h"

class Nodo: public iNodo
{
	private:
		eTipoNodo tipo;
		size_t tamanio;
		size_t cantidadRegistros;
		iRegistroPtr *tablaRegistros;
		size_t pivote;
		float radio;

		virtual ~Nodo();
	public:
		Nodo(eTipoNodo tipo, iRegistroPtr *listaRegistros, size_t cantidadRegistros, size_t pivote, float radio);

		virtual void Dispose();

		virtual eTipoNodo ObtenerTipoNodo();
		virtual void CambiarTipoNodo(eTipoNodo nuevoTipo);

		virtual size_t ObtenerPivote();
		virtual float ObtenerRadio();

		virtual size_t ObtenerCantidadRegistros();
		virtual iRegistroPtr ObtenerRegistro(size_t pos);

		virtual iRegistroPtr AgregarRegistro(iRegistroPtr reg);
		virtual iRegistroPtr QuitarRegistro(size_t clave);

	private:
		void RedimensionarTabla(size_t nuevoTamanio);
};

#endif	/* NODO_H */

