/* 
 * File:   iNodoArbolPuntoOptimo.h
 * Author: Monty
 *
 * Created on 24 de mayo de 2016, 00:03
 */

#ifndef INODOARBOLPUNTOOPTIMO_H
#define INODOARBOLPUNTOOPTIMO_H

#include "../../Nodo/Headers/iNodo.h"

enum eNodoArbolPuntoOptimo {
	eNodoArbolPuntoOptimo_Hoja, eNodoArbolPuntoOptimo_Interno
};

typedef class iNodoArbolPuntoOptimo: public iNodo {

public:

	virtual iNodoArbolPuntoOptimo *Copiar() = 0;
	virtual iNodoArbolPuntoOptimo *Clone() = 0;
	virtual eNodoArbolPuntoOptimo ObtenerTipoNodo() = 0;

}*iNodoArbolPuntoOptimoPtr;

typedef class iNodoArbolPuntoOptimoNodoHoja: public iNodoArbolPuntoOptimo {

}*iNodoArbolPuntoOptimoNodoHojaPtr;

typedef class iNodoArbolPuntoOptimoNodoInterno: public iNodoArbolPuntoOptimo {

public:

	virtual iFeaturePtr ObtenerPivote() = 0;
	virtual void EstablecerPivote(iFeaturePtr pivote) = 0;

	virtual float ObtenerRadio() = 0;
	virtual void EstablecerRadio(float radio) = 0;

	virtual void EstablecerHijoIzquierdo(size_t nodo) = 0;
	virtual size_t ObtenerHijoIzquierdo() = 0;
	virtual void EstablecerHijoDerecho(size_t nodo) = 0;
	virtual size_t ObtenerHijoDerecho() = 0;

}*iNodoArbolPuntoOptimoNodoInternoPtr;

#endif /* INODOARBOLPUNTOOPTIMO_H */
