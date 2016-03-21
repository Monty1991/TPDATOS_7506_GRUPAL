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

		virtual unsigned char AsEntero8SinSigno() = 0;
		virtual unsigned short AsEntero16SinSigno() = 0;
		virtual unsigned int AsEntero32SinSigno() = 0;
		virtual unsigned long long int AsEntero64SinSigno() = 0;

		virtual char AsEntero8ConSigno() = 0;
		virtual short AsEntero16ConSigno() = 0;
		virtual int AsEntero32ConSigno() = 0;
		virtual long long int AsEntero64ConSigno() = 0;

		virtual float AsFlotante32() = 0;
		virtual double AsFlotante64() = 0;

		virtual sCadenaANSI AsCadenaANSI() = 0;
		virtual sCadenaUNICODE AsCadenaUNICODE() = 0;

		virtual iRegistroPtr AsRegistro() = 0;

		virtual void Dispose() = 0;

} *iFeaturePtr;

#endif	/* IFEATURE_H */
