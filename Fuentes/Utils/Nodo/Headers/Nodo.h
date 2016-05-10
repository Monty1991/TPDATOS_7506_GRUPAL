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
		size_t cantidad;
		iRegistroPtr *tablaRegistros;
		
	public:
		Nodo(eTipoNodo tipo, iRegistroPtr *listaRegistros, size_t cantidadRegistros);
		virtual ~Nodo();

		virtual void Dispose();

		virtual eTipoNodo ObtenerTipoNodo();
		virtual void CambiarTipoNodo(eTipoNodo nuevoTipo);

		virtual size_t ObtenerCantidadRegistros();
		virtual iRegistroPtr ObtenerRegistro(size_t pos);

		virtual iRegistroPtr AgregarRegistro(iRegistroPtr reg);
		virtual iRegistroPtr QuitarRegistro(size_t pos);
};

#endif	/* NODO_H */

