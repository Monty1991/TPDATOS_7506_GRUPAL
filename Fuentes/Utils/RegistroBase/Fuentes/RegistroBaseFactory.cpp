#include "../RegistroBaseFactory.h"
#include "../Headers/RegistroBase.h"

iRegistroBasePtr RegistroBaseFactory_Nuevo(size_t cantidadCampos)
{
	return new RegistroBase(cantidadCampos);
}
