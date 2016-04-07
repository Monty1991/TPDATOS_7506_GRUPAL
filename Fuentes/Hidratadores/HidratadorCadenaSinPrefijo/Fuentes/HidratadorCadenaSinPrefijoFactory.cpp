#include "../HidratadorCadenaSinPrefijoFactory.h"
#include "../Headers/HidratadorCadenaSinPrefijo.h"

iHidratadorCadenaSinPrefijoPtr HidratadorCadenaSinPrefijoFactory_Nuevo()
{
	return new HidratadorCadenaSinPrefijo();
}
