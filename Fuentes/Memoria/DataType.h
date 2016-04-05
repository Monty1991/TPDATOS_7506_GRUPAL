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

/*
 * Formato numerico
 * R = 0, N = 1, F, S, T1, T2
 * R: 0 - Primitivo / 1 - Registro
 * N: 1 - Numerico / 0 - No Numerico
 * F: 0 - Entero / 1 - Flotante
 * S: 0 - Sin signo / 1 - Con signo
 * T1T2: 00 - 8 bits / 01 - 16 bits / 10 - 32 bits / 11 - 64 bits
 * 
 * Formato Cadena
 * R = 0, N = 0, X, X, X, U
 * R: 0 - Primitivo / 1 - Registro
 * N: 1 - Numerico / 0 - No numerico
 * X: No importa
 * U: 0 - ANSI / 1 - UNICODE
 */

#define Mascara_8Bits 0x00		// 0000 0000	(T1, T2)
#define Mascara_16Bits 0x01		// 0000 0001	(T1, T2)
#define Mascara_32Bits 0x02		// 0000 0010	(T1, T2)
#define Mascara_64Bits 0x03		// 0000 0011	(T1, T2)
#define Mascara_Unicode 0x01	// 0000 0001	(U)
#define Mascara_Signo 0x04		// 0000 0100	(S)
#define Mascara_Flotante 0x08	// 0000 1000	(F)
#define Mascara_Numero 0x10		// 0001 0000	(N)
#define Mascara_Registro 0x20	// 0010 0000	(R)

typedef enum eValueType
{
	eValueType_I1 = Mascara_Numero | Mascara_Signo | Mascara_8Bits,							//	Entero 1 byte con signo
	eValueType_U1 = Mascara_Numero | Mascara_8Bits,											//	Entero 1 byte sin signo
	eValueType_I2 = Mascara_Numero | Mascara_Signo | Mascara_16Bits,						//	Entero 2 bytes sin signo
	eValueType_U2 = Mascara_Numero | Mascara_16Bits,										//	Entero 2 bytes sin signo
	eValueType_I4 = Mascara_Numero | Mascara_Signo | Mascara_32Bits,						//	Entero 4 bytes sin signo
	eValueType_U4 = Mascara_Numero | Mascara_32Bits,										//	Entero 4 bytes sin signo
	eValueType_I8 = Mascara_Numero | Mascara_Signo | Mascara_64Bits,						//	Entero 8 bytes sin signo
	eValueType_U8 = Mascara_Numero | Mascara_64Bits,										//	Entero 8 bytes sin signo
	eValueType_F32 = Mascara_Numero | Mascara_Flotante | Mascara_Signo | Mascara_32Bits,	//	Flotante IEEE754 32 bits
	eValueType_F64 = Mascara_Numero | Mascara_Flotante | Mascara_Signo | Mascara_64Bits,	//	Flotante IEEE754 64 bits
	eValueType_CA,	//	Cadena ANSI
	eValueType_CU = Mascara_Unicode,	//	Cadena UNICODE
	eValueType_R = Mascara_Registro,	//	Registro
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
	unsigned __int8 entero8SinSigno;
	unsigned __int16 entero16SinSigno;
	unsigned __int32 entero32SinSigno;
	unsigned __int64 entero64SinSigno;
};

union uEnteroConSigno
{
	__int8 entero8ConSigno;
	__int16 entero16ConSigno;
	__int32 entero32ConSigno;
	__int64 entero64ConSigno;	
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
