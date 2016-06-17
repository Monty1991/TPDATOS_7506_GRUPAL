#include "../ComandoCargaFactory.h"
#include "../Headers/ComandoCarga.h"

iComandoCargaPtr ComandoCargaFactory_Nuevo()
{
	return new ComandoCarga();
}
