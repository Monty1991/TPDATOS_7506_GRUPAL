/* 
 * File:   StringUtils.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 20:41
 */

#ifndef STRINGUTILS_H
#define	STRINGUTILS_H

#include <stdio.h>

#define StringUtils_Concatenar(out, format, ...) sprintf(out, format, __VA_ARGS__)

char *StringUtils_Clonar(const char *cadena);

#endif	/* STRINGUTILS_H */
