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

		unsigned char AsEntero8SinSigno();
		unsigned short AsEntero16SinSigno();
		unsigned int AsEntero32SinSigno();
		unsigned long long int AsEntero64SinSigno();
		
		char AsEntero8ConSigno();
		short AsEntero16ConSigno();
		int AsEntero32ConSigno();
		long long int AsEntero64ConSigno();

		float AsFlotante32();
		double AsFlotante64();

		sCadenaANSI AsCadenaANSI();
		sCadenaUNICODE AsCadenaUNICODE();

		iRegistroPtr AsRegistro();

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

