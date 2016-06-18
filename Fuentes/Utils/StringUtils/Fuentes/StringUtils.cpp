#include "../Headers/StringUtils.h"
#include "../../NumberUtils/Headers/NumberUtils.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"
#include <stdio.h>
#include <string.h>

char *StringUtils_Clonar(const char *cadena)
{
	char *nuevaCadena = new char[strlen(cadena) + 1];
	strcpy(nuevaCadena, cadena);
	
	return nuevaCadena;
}

size_t StringUtils_CalcularEspacioSerializacion(const sCadenaANSI *cadena)
{
	size_t espacioSerializacion = 0;

	espacioSerializacion += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U2);
	espacioSerializacion += cadena->largo;

	return espacioSerializacion;
}

size_t StringUtils_CalcularEspacioSerializacion(const sCadenaUNICODE *cadena)
{
	size_t espacioSerializacion = 0;

	espacioSerializacion += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U2);
	espacioSerializacion += cadena->largo * sizeof(wchar_t);

	return espacioSerializacion;
}

size_t StringUtils_Serializar(char *buff, const char *cadena, size_t largo)
{
	memcpy(buff, cadena, largo);
	return largo;
}

size_t StringUtils_Serializar(char *buff, const sCadenaANSI *cadena)
{
	size_t espacioSerializacion = 0;

	uNumber largo;
	largo.entero.enteroSinSigno.entero16SinSigno = cadena->largo;
	espacioSerializacion += NumberUtils_Serializar(buff + espacioSerializacion, largo, eValueType::eValueType_U2);
	espacioSerializacion += StringUtils_Serializar(buff + espacioSerializacion, cadena->cadena, cadena->largo);

	return espacioSerializacion;
}

size_t StringUtils_Serializar(char *buff, const sCadenaUNICODE *cadena)
{
	size_t espacioSerializacion = 0;

	uNumber largo;
	largo.entero.enteroSinSigno.entero16SinSigno = cadena->largo;
	espacioSerializacion += NumberUtils_Serializar(buff + espacioSerializacion, largo, eValueType::eValueType_U2);
	espacioSerializacion += StringUtils_Serializar(buff + espacioSerializacion, (char *)cadena->cadena, cadena->largo * sizeof(wchar_t));

	return espacioSerializacion;
}

size_t StringUtils_Hidratar(const char *buff, char *cadena, size_t largo)
{
	memcpy(cadena, buff, largo);
	return largo;
}

size_t StringUtils_Hidratar(const char *buff, sCadenaANSI *cadena)
{
	uNumber largo;
	largo.entero.enteroSinSigno.entero64SinSigno = 0;
	size_t leido = 0;

	leido = NumberUtils_Hidratar(buff + leido, &largo, eValueType::eValueType_U2);
	size_t largoCadena = largo.entero.enteroSinSigno.entero16SinSigno;

	cadena->cadena = new char[largoCadena];
	cadena->largo = largoCadena;

	leido += StringUtils_Hidratar(buff + leido, cadena->cadena, largoCadena);

	return leido;
}

size_t StringUtils_Hidratar(const char *buff, sCadenaUNICODE *cadena)
{
	uNumber largo;
	largo.entero.enteroSinSigno.entero64SinSigno = 0;
	size_t leido = 0;

	leido = NumberUtils_Hidratar(buff + leido, &largo, eValueType::eValueType_U2);
	size_t largoCadena = largo.entero.enteroSinSigno.entero16SinSigno;

	cadena->cadena = new wchar_t[largoCadena];
	cadena->largo = largoCadena;

	leido += StringUtils_Hidratar(buff + leido, (char *)(cadena->cadena), largoCadena * sizeof(wchar_t));

	return leido;
}
