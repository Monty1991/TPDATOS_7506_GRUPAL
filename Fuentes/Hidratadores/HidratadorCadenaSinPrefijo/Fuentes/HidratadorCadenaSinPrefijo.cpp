#include "../Headers/HidratadorCadenaSinPrefijo.h"

#include <string>

HidratadorCadenaSinPrefijo::HidratadorCadenaSinPrefijo()
{

}

HidratadorCadenaSinPrefijo::~HidratadorCadenaSinPrefijo()
{

}

size_t HidratadorCadenaSinPrefijo::Hidratar(char *buff, char *cadena, size_t largo)
{
	memcpy(cadena, buff, largo);
	return largo;
}

void HidratadorCadenaSinPrefijo::Dispose()
{
	delete this;
}
