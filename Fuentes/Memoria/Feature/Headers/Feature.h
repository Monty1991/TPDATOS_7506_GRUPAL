/* 
 * File:   Feature.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 05:21
 */

#ifndef FEATURE_H
#define	FEATURE_H

#include "iFeature.h"

class Feature: public iFeature
{
	private:
		uValue contenido;
		eValueType tipo;
		
	public:
		Feature(uValue valor, eValueType tipo);
		virtual ~Feature();

		unsigned INT8 AsEntero8SinSigno();
		unsigned INT16 AsEntero16SinSigno();
		unsigned INT32 AsEntero32SinSigno();
		unsigned INT64 AsEntero64SinSigno();
		
		INT8 AsEntero8ConSigno();
		INT16 AsEntero16ConSigno();
		INT32 AsEntero32ConSigno();
		INT64 AsEntero64ConSigno();

		float AsFlotante32();
		double AsFlotante64();

		sCadenaANSI AsCadenaANSI();
		sCadenaUNICODE AsCadenaUNICODE();

		iObjectPtr AsRegistro();

		virtual void Dispose();

	private:
		uPrimitive AsPrimitive();
		uCadena AsCadena();
		uNumber AsNumber();
		uFlotante AsFlotante();
		uEntero AsEntero();
		uEnteroSinSigno AsEnteroSinSigno();
		uEnteroConSigno AsEnteroConSigno();

};

#endif	/* FEATURE_H */

