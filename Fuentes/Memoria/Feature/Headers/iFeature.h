/* 
 * File:   iFeature.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 05:51
 */

#ifndef IFEATURE_H
#define	IFEATURE_H

#include "../../DataType.h"

typedef class iFeature
{
	public:

		virtual unsigned INT8 AsEntero8SinSigno() = 0;
		virtual unsigned INT16 AsEntero16SinSigno() = 0;
		virtual unsigned INT32 AsEntero32SinSigno() = 0;
		virtual unsigned INT64 AsEntero64SinSigno() = 0;

		virtual INT8 AsEntero8ConSigno() = 0;
		virtual INT16 AsEntero16ConSigno() = 0;
		virtual INT32 AsEntero32ConSigno() = 0;
		virtual INT64 AsEntero64ConSigno() = 0;

		virtual float AsFlotante32() = 0;
		virtual double AsFlotante64() = 0;

		virtual sCadenaANSI AsCadenaANSI() = 0;
		virtual sCadenaUNICODE AsCadenaUNICODE() = 0;

		virtual iObjectPtr AsRegistro() = 0;

		virtual void Dispose() = 0;

} *iFeaturePtr;

#endif	/* IFEATURE_H */
