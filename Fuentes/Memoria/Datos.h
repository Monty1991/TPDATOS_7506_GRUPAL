/* 
 * File:   Datos.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 12:29
 */

#ifndef DATOS_H
#define	DATOS_H

#include <stddef.h>

struct StringPascal
{
	char longitud;
	char *cadena;
};

union uValue
{
	char caracter;
	short mediaPalabra;
	int palabra;
	long long palabraDoble;
	float flotanteSimple;
	double flotanteDoble;
	StringPascal *stringPascal;
};

enum eValueType
{
	eValueType_caracter,
	eValueType_mediaPalabra,
	eValueType_palabra,
	eValueType_palabraDoble,
	eValueType_flotanteSimple,
	eValueType_flotanteDoble,
	eValueType_stringPascal,
};

#endif	/* DATOS_H */
