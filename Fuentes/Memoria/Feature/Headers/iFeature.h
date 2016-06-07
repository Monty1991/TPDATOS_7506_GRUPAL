/* 
 * File:   iFeature.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 05:51
 */

#ifndef IFEATURE_H
#define	IFEATURE_H

#include "../../DataType.h"

typedef class iFeature: public iObject
{
	public:
		virtual eValueType ObtenerTipo() = 0;

		virtual iFeature *Copiar() = 0;
		virtual iFeature *Clone() = 0;
		
		virtual uNumber AsNumber() = 0;
		virtual sCadenaANSI *AsCadenaANSI() = 0;
		virtual sCadenaUNICODE *AsCadenaUNICODE() = 0;
		virtual iObjectPtr AsRegistro() = 0;

		virtual void Dispose() = 0;
} *iFeaturePtr;

#endif	/* IFEATURE_H */
