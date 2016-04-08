#include "../HidratadorCadenaANSIFactory.h"
#include "../Headers/HidratadorCadenaANSI.h"

iHidratadorCadenaANSIPtr HidratadorCadenaANSIFactory_Nuevo()
{
	return new HidratadorCadenaANSI();
}
