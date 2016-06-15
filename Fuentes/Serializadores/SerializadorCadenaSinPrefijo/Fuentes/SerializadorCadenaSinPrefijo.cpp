#include "../Headers/SerializadorCadenaSinPrefijo.h"
#include <string.h>

SerializadorCadenaSinPrefijo::SerializadorCadenaSinPrefijo()
{
	
}

SerializadorCadenaSinPrefijo::~SerializadorCadenaSinPrefijo()
{
	
}

size_t SerializadorCadenaSinPrefijo::CalcularEspacio(char *cadena, size_t tamanio)
{
	return tamanio;
}

size_t SerializadorCadenaSinPrefijo::Serializar(char *buff, char *cadena, size_t tamanio)
{
	memcpy(buff, cadena, tamanio);
	return tamanio;
}

void SerializadorCadenaSinPrefijo::Dispose()
{
	delete this;
}

