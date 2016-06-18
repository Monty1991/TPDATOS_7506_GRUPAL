/* 
 * File:   Feature.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 05:21
 */

#ifndef FEATURE_H
#define	FEATURE_H

#include "iFeature.h"
#include "../../Object/Headers/Object.h"

class Feature: public iFeature, public Object
{
	private:
		uValue contenido;
		eValueType tipo;
		
		virtual ~Feature();
	public:
		Feature(uValue valor, eValueType tipo);
		Feature(sCadenaANSI *cadenaAnsi);

		virtual iFeaturePtr Copiar();
		virtual iFeaturePtr Clone();

		virtual eValueType ObtenerTipo();

		virtual uNumber AsNumber();
		virtual sCadenaANSI *AsCadenaANSI();
		virtual sCadenaUNICODE *AsCadenaUNICODE();
		virtual iObjectPtr AsRegistro();

		virtual int Comparar(iFeature *feature);

		virtual size_t GenerarHash();

		virtual void Dispose();

	private:
};

#endif	/* FEATURE_H */
