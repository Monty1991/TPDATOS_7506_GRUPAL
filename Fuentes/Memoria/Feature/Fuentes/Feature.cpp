/* 
 * File:   Feature.cpp
 * Author: Monty
 * 
 * Created on 21 de marzo de 2016, 05:21
 */

#include <string.h>
#include <wchar.h>

#include "../Headers/Feature.h"

Feature::Feature(uValue valor, eValueType tipo): Object(), contenido(valor), tipo(tipo)
{
	if (this->tipo & Mascara_Numero)
		this->contenido.primitivo.numero = valor.primitivo.numero;
	else if (this->tipo & Mascara_Unicode)
	{
		size_t largo = valor.primitivo.cadena.unicode.largo;
		wchar_t *cadena = new wchar_t[largo];
		memcpy(cadena, valor.primitivo.cadena.unicode.cadena, largo * sizeof(wchar_t));
		
		this->contenido.primitivo.cadena.unicode.largo = largo;
		this->contenido.primitivo.cadena.unicode.cadena = cadena;
	}
	else
	{
		size_t largo = valor.primitivo.cadena.ansi.largo;
		char *cadena = new char[largo];
		memcpy(cadena, valor.primitivo.cadena.ansi.cadena, largo);
		
		this->contenido.primitivo.cadena.ansi.largo = largo;
		this->contenido.primitivo.cadena.ansi.cadena = cadena;
	}
}

Feature::Feature(sCadenaANSI *cadena): Object(), tipo(eValueType::eValueType_CA)
{
	size_t largo = cadena->largo;
	char *nuevaCadena = new char[largo];
	memcpy(nuevaCadena, cadena->cadena, largo);

	this->contenido.primitivo.cadena.ansi.largo = largo;
	this->contenido.primitivo.cadena.ansi.cadena = nuevaCadena;
}

Feature::~Feature()
{
	if (!(this->tipo & Mascara_Numero))
	{
		if (this->tipo & Mascara_Unicode)
		{
			sCadenaUNICODE *cadena = this->AsCadenaUNICODE();
			if (cadena->cadena)
				delete [] cadena->cadena;
		}
		else
		{
			sCadenaANSI *cadena = this->AsCadenaANSI();
			if (cadena->cadena)
				delete [] cadena->cadena;
		}
	}
}

iFeaturePtr Feature::Copiar()
{
	Object::IncrementarContador();
	return this;
}

iFeaturePtr Feature::Clone()
{
	return new Feature(this->contenido, this->tipo);
}

eValueType Feature::ObtenerTipo()
{
	return this->tipo;
}

uNumber Feature::AsNumber()
{
	return this->contenido.primitivo.numero;
}

sCadenaANSI *Feature::AsCadenaANSI()
{
	return &(this->contenido.primitivo.cadena.ansi);
}

sCadenaUNICODE *Feature::AsCadenaUNICODE()
{
	return &(this->contenido.primitivo.cadena.unicode);
}

iObjectPtr Feature::AsRegistro()
{
	return this->contenido.registro;
}

void Feature::Dispose()
{
	Object::Dispose();
}
