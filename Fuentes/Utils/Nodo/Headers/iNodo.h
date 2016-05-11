/* 
 * File:   iNodo.h
 * Author: Monty
 *
 * Created on 25 de abril de 2016, 22:43
 */

#ifndef INODO_H
#define	INODO_H

#include "../../../Memoria/Registro/Headers/iRegistro.h"

enum eEstadoCargaNodo
{
	eEstadoCargaNodo_Underflow,
	eEstadoCargaNodo_CargaMinima,
	eEstadoCargaNodo_NoCargaMinima,
	eEstadoCargaNodo_Overflow,
};

enum eTipoNodo
{
	eTipoNodo_Hoja,
	eTipoNodo_NodoInterno
};

typedef class iNodo
{
	public:
		virtual eTipoNodo ObtenerTipoNodo() = 0;
		virtual void CambiarTipoNodo(eTipoNodo nuevoTipo) = 0;

//		virtual size_t ObtenerPivote() = 0;
//		virtual float ObtenerRadio() = 0;
//		virtual void CambiarPivote(size_t nuevoPivote) = 0;
//		virtual void CambiarRadio(float nuevoRadio) = 0;
		
		virtual size_t ObtenerCantidadRegistros() = 0;
		virtual iRegistroPtr ObtenerRegistro(size_t pos) = 0;

		virtual iRegistroPtr AgregarRegistro(iRegistroPtr reg) = 0;
		virtual iRegistroPtr QuitarRegistro(size_t clave) = 0;

		virtual void Dispose() = 0;
} *iNodoPtr;

#endif	/* INODO_H */
