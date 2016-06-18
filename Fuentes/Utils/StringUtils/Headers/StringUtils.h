/* 
 * File:   StringUtils.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 20:41
 */

#ifndef STRINGUTILS_H
#define	STRINGUTILS_H

#include <stdio.h>
#include "../../../Memoria/DataType.h"

#define StringUtils_Concatenar(out, format, ...) sprintf(out, format, __VA_ARGS__)

char *StringUtils_Clonar(const char *cadena);

size_t StringUtils_CalcularEspacioSerializacion(const sCadenaANSI *cadena);
size_t StringUtils_CalcularEspacioSerializacion(const sCadenaUNICODE *cadena);

size_t StringUtils_Serializar(char *buff, const char *cadena, size_t largo);
size_t StringUtils_Serializar(char *buff, const sCadenaANSI *cadena);
size_t StringUtils_Serializar(char *buff, const sCadenaUNICODE *cadena);

size_t StringUtils_Hidratar(const char *buff, char *cadena, size_t largo);
size_t StringUtils_Hidratar(const char *buff, sCadenaANSI *cadena);
size_t StringUtils_Hidratar(const char *buff, sCadenaUNICODE *cadena);

#endif	/* STRINGUTILS_H */
