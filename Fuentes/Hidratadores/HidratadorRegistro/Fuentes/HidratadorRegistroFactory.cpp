#include "../HidratadorRegistroFactory.h"
#include "../Headers/HidratadorRegistro.h"

iHidratadorRegistroPtr HidratadorRegistroFactory_Nuevo()
{
	return new HidratadorRegistro();
}
