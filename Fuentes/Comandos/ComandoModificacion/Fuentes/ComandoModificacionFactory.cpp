#include "../ComandoModificacionFactory.h"
#include "../Headers/ComandoModificacion.h"

iComandoModificacionPtr ComandoModificacionFactory_Nuevo()
{
	return new ComandoModificacion();
}
