/* 
 * File:   Feature.cpp
 * Author: Monty
 * 
 * Created on 21 de marzo de 2016, 05:21
 */

#include "../Headers/Feature.h"

Feature::Feature(uValue valor, eValueType tipo): contenido(valor), tipo(tipo)
{
}

Feature::~Feature()
{
	if (this->tipo & Mascara_Registro)
		delete this->AsRegistro();
	else if (this->tipo ^ Mascara_Numero)
	{
		if (this->tipo & Mascara_Unicode)
			delete this->AsCadenaUNICODE().cadena;
		else
			delete this->AsCadenaANSI().cadena;
	}
}

unsigned char Feature::AsEntero8SinSigno()
{
	return this->AsEnteroSinSigno().entero8SinSigno;
}

unsigned short Feature::AsEntero16SinSigno()
{
	return this->AsEnteroSinSigno().entero16SinSigno;
}

unsigned int Feature::AsEntero32SinSigno()
{
	return this->AsEnteroSinSigno().entero32SinSigno;
}

unsigned long long int Feature::AsEntero64SinSigno()
{
	return this->AsEnteroSinSigno().entero64SinSigno;
}

char Feature::AsEntero8ConSigno()
{
	return this->AsEnteroConSigno().entero8ConSigno;
}

short Feature::AsEntero16ConSigno()
{
	return this->AsEnteroConSigno().entero16ConSigno;
}

int Feature::AsEntero32ConSigno()
{
	return this->AsEnteroConSigno().entero32ConSigno;
}

long long int Feature::AsEntero64ConSigno()
{
	return this->AsEnteroConSigno().entero64ConSigno;
}

float Feature::AsFlotante32()
{
	return this->AsFlotante().flotante32;
}

double Feature::AsFlotante64()
{
	return this->AsFlotante().flotante64;	
}

sCadenaANSI Feature::AsCadenaANSI()
{
	return this->AsCadena().ansi;
}

sCadenaUNICODE Feature::AsCadenaUNICODE()
{
	return this->AsCadena().unicode;	
}

iObjectPtr Feature::AsRegistro()
{
	return this->contenido.registro;
}

void Feature::Dispose()
{
	delete this;
}

uPrimitive Feature::AsPrimitive()
{
	return this->contenido.primitivo;
}

uCadena Feature::AsCadena()
{
	return this->AsPrimitive().cadena;
}

uNumber Feature::AsNumber()
{
	return this->AsPrimitive().numero;
}

uFlotante Feature::AsFlotante()
{
	return this->AsNumber().flotante;
}

uEntero Feature::AsEntero()
{
	return this->AsNumber().entero;
}

uEnteroSinSigno Feature::AsEnteroSinSigno()
{
	return this->AsEntero().enteroSinSigno;
}

uEnteroConSigno Feature::AsEnteroConSigno()
{
	return this->AsEntero().enteroConSigno;
}
