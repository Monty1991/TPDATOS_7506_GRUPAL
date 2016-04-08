#include "../HidratadorCadenaUNICODEFactory.h"
#include "../Headers/HidratadorCadenaUNICODE.h"

iHidratadorCadenaUNICODEPtr HidratadorCadenaUNICODEFactory_Nuevo()
{
	return new HidratadorCadenaUNICODE();
}
