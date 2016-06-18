/* 
 * File:   NumberUtils.h
 * Author: Monty
 *
 * Created on 18 de junio de 2016, 03:21
 */

#ifndef NUMBERUTILS_H
#define NUMBERUTILS_H

#include "../../../Memoria/DataType.h"

size_t NumberUtils_CalcularEspacioSerializacion(eValueType tipo);
size_t NumberUtils_Serializar(char *buff, uNumber numero, eValueType tipo);
size_t NumberUtils_Hidratar(const char *buff, uNumber *numero, eValueType tipo);

#endif /* NUMBERUTILS_H */
