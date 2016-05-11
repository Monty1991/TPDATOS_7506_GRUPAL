#include "../HidratadorNodoFactory.h"
#include "../Headers/HidratadorNodo.h"

iHidratadorNodoPtr HidratadorNodoFactory_Nuevo()
{
	return new HidratadorNodo();
}
