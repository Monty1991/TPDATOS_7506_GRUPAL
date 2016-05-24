#include "../HidratadorNodoArbolPuntoOptimoFactory.h"
#include "../Headers/HidratadorNodoArbolPuntoOptimo.h"

iHidratadorNodoPtr HidratadorNodoArbolPuntoOptimoFactory_Nuevo()
{
	return new HidratadorNodoArbolPuntoOptimo();
}
