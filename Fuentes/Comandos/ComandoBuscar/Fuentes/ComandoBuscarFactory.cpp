#include "../ComandoBuscarFactory.h"
#include "../Headers/ComandoBuscar.h"

iComandoBuscarPtr ComandoBuscarFactory_Nuevo()
{
	return new ComandoBuscar();
}
