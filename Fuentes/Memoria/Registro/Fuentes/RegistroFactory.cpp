#include "../RegistroFactory.h"
#include "../Headers/Registro.h"
#include "../../Feature/FeatureFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

iRegistroPtr RegistroFactory_Nuevo(size_t cantidadCampos)
{
	return new Registro(cantidadCampos);
}

iRegistroPtr RegistroFactory_Nuevo(iDescriptorRegistroPtr descriptor, const char *cadena)
{
	if (!descriptor || !cadena)
		return NULL;

	iRegistroPtr registro = RegistroFactory_Nuevo(descriptor->ObtenerCantidadCampos());
	char *cadenaRegistro = (char *)cadena;
	iFeaturePtr campo = NULL;
	for (size_t i = 0; i < descriptor->ObtenerCantidadCampos(); i++)
	{
		Sistema_Execute(campo = FeatureFactory_Nuevo(descriptor->ObtenerDescriptorCampo(i), cadenaRegistro, &cadenaRegistro););
		Sistema_Execute(registro->SetFeature(i, campo););

		// llegados aquí, se leyo hasta la coma
		cadenaRegistro++;
	}

	return registro;
}
