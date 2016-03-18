#include "../Headers/StringUtils.h"
#include <stdio.h>
#include <string.h>

char *StringUtils_Clonar(const char *cadena)
{
	char *nuevaCadena = new char[strlen(cadena) + 1];
	strcpy(nuevaCadena, cadena);
	
	return nuevaCadena;
}
