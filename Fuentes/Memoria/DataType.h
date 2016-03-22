/* 
 * File:   DataType.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 04:55
 */

#ifndef DATATYPE_H
#define	DATATYPE_H

#include <stddef.h>
#include "Object/Headers/iObject.h"

typedef enum eValueType
{
	eValueType_I1,	//	Entero 1 byte con signo
	eValueType_U1,	//	Entero 1 byte sin signo
	eValueType_I2,	//	Entero 2 bytes sin signo
	eValueType_U2,	//	Entero 2 bytes sin signo
	eValueType_I4,	//	Entero 4 bytes sin signo
	eValueType_U4,	//	Entero 4 bytes sin signo
	eValueType_I8,	//	Entero 8 bytes sin signo
	eValueType_U8,	//	Entero 8 bytes sin signo
	eValueType_F32,	//	Flotante IEEE754 32 bits
	eValueType_F64,	//	Flotante IEEE754 64 bits
	eValueType_CA,	//	Cadena ANSI
	eValueType_CU,	//	Cadena UNICODE
	eValueType_R,	//	Registro
} *eValueTypePtr;

struct sCadenaANSI
{
	size_t largo;
	char *cadena;
};

struct sCadenaUNICODE
{
	size_t largo;
	wchar_t *cadena;
};

union uCadena
{
	sCadenaANSI ansi;
	sCadenaUNICODE unicode;
};

union uEnteroSinSigno
{
	unsigned char entero8SinSigno;
	unsigned short entero16SinSigno;
	unsigned int entero32SinSigno;
	unsigned long long int entero64SinSigno;
};

union uEnteroConSigno
{
	char entero8ConSigno;
	short entero16ConSigno;
	int entero32ConSigno;
	long long int entero64ConSigno;	
};

union uEntero
{
	uEnteroSinSigno enteroSinSigno;
	uEnteroConSigno enteroConSigno;
};

union uFlotante
{
	float flotante32;
	double flotante64;
};

union uNumber
{
	uEntero entero;
	uFlotante flotante;
};

union uPrimitive
{
	uNumber numero;
	uCadena cadena;
};

union uValue
{
	uPrimitive primitivo;
	iObjectPtr registro;
};

#endif	/* DATATYPE_H */
