#include "../EntornoFactory.h"
#include "../Headers/Entorno.h"

iEntornoPtr EntornoFactory_Nuevo()
{
	return new Entorno();
}
