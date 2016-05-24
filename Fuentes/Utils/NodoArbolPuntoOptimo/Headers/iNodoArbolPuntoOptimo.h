/* 
 * File:   iNodoArbolPuntoOptimo.h
 * Author: Monty
 *
 * Created on 24 de mayo de 2016, 00:03
 */

#ifndef INODOARBOLPUNTOOPTIMO_H
#define INODOARBOLPUNTOOPTIMO_H

#include "../../Nodo/Headers/iNodo.h"

enum eNodoArbolPuntoOptimo
{
	eNodoArbolPuntoOptimo_Hoja,
	eNodoArbolPuntoOptimo_Interno
};

typedef class iNodoArbolPuntoOptimoNodoHoja: public iNodo
{
	public:
		virtual eNodoArbolPuntoOptimo ObtenerTipoNodo() = 0;

} *iNodoArbolPuntoOptimoNodoHojaPtr;

typedef class iNodoArbolPuntoOptimoNodoInterno: public iNodoArbolPuntoOptimoNodoHoja
{
	public:
		virtual size_t ObtenerPivote() = 0;
		virtual void EstablecerPivote(size_t pivote) = 0;
		
		virtual float ObtenerRadio() = 0;
		virtual void EstablecerRadio(float radio) = 0;

} *iNodoArbolPuntoOptimoNodoInternoPtr;

#endif /* INODOARBOLPUNTOOPTIMO_H */
