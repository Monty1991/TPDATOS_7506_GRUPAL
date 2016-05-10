#include "../RegistroFactory.h"
#include "../Headers/Registro.h"

iRegistroPtr RegistroFactory_Nuevo(size_t cantidadCampos)
{
	return new Registro(cantidadCampos);
}
