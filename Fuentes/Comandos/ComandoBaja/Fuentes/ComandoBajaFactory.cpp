#include "../ComandoBajaFactory.h"
#include "../Headers/ComandoBaja.h"

iComandoBajaPtr ComandoBajaFactory_Nuevo()
{
	return new ComandoBaja();
}
