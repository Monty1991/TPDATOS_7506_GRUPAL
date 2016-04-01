#include "../BloqueRegistroFactory.h"
#include "../Headers/BloqueRegistro.h"

iBloqueRegistroPtr BloqueRegistroFactory_Nuevo()
{
	return new BloqueRegistro();
}
