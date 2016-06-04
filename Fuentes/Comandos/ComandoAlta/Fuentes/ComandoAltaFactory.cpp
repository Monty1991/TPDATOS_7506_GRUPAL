#include "../ComandoAltaFactory.h"
#include "../Headers/ComandoAlta.h"

iComandoAltaPtr ComandoAltaFactory_Nuevo()
{
	return new ComandoAlta();
}
