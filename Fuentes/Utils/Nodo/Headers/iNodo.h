/* 
 * File:   iNodo.h
 * Author: Monty
 *
 * Created on 25 de abril de 2016, 22:43
 */

#ifndef INODO_H
#define	INODO_H

#include "../../../Memoria/Registro/Headers/iRegistro.h"

#include <functional>

// Funcion que recibe un registro y decide si avanzar o no
// Sirve para implementar iteradores
typedef std::function<bool(iRegistroPtr)> IteratorFunction;

enum eEstadoCargaNodo
{
	eEstadoCargaNodo_Underflow,
	eEstadoCargaNodo_CargaMinima,
	eEstadoCargaNodo_NoCargaMinima,
	eEstadoCargaNodo_Overflow,
};

enum eTipoArbol
{
	eTipoArbol_ArbolPuntoOptimo
};

typedef class iNodo: public iObject
{
	public:
		virtual iNodo *Copiar() = 0;
		virtual iNodo *Clone() = 0;

		virtual eTipoArbol ObtenerTipoArbol() = 0;

		virtual size_t ObtenerCantidadRegistros() = 0;
		virtual iRegistroPtr ObtenerRegistro(size_t pos) = 0;

		virtual void AgregarRegistro(iRegistroPtr reg) = 0;
		virtual iRegistroPtr QuitarRegistro(size_t pos) = 0;
		virtual iRegistroPtr QuitarRegistro() = 0;

		virtual size_t BuscarRegistro(iFeaturePtr clave, size_t nroCampoClave) = 0;
		
		// Itera por los registros;
		virtual void Iterar(IteratorFunction iterador) = 0;

		virtual void Dispose() = 0;
} *iNodoPtr;

#endif	/* INODO_H */
