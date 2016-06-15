#include "../DescriptorRegistroFactory.h"
#include "../Headers/DescriptorRegistro.h"
#include "../../../Exceptions/ExceptionFactory.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(const sDescriptorCampoPtr tablaDescriptorCampo, size_t cantidadDescriptoresCampo)
{
	return new DescriptorRegistro(tablaDescriptorCampo, cantidadDescriptoresCampo);
}

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(const char *cadenaDescriptorRegistro)
{
	size_t cuentaComas = 1;	// como minimo hay 1 campo
	
	while (*cadenaDescriptorRegistro == ' ')
		cadenaDescriptorRegistro++;

	for (const char *i = cadenaDescriptorRegistro; *i != '\0'; i++)
		if (*i == ',')
			cuentaComas++;

	sDescriptorCampo descriptor[cuentaComas];
	size_t campoActual = 0;
	const char *punteroCadena = cadenaDescriptorRegistro;
	while (true)
	{
		if (*punteroCadena == '\0')
			break;

		if (*punteroCadena == ',')
		{
			punteroCadena++;
			continue;
		}

		eDescriptorCampo descCampo = IdentificarDescriptorCampo(*punteroCadena);
		
		// Problemas, debiera tirar excepcion
		if (descCampo == eDescriptorCampo::eDescriptorCampo_Unknown)
			Throw("Bad format", "eDescriptorCampo_Unknown");

		punteroCadena++;
		size_t modificador = 0;
		while ((*punteroCadena != ',') && (*punteroCadena != '\0'))
		{
			if ((*punteroCadena >= '0') && (*punteroCadena <= '9'))
			{
				modificador *= 10;
				modificador += *punteroCadena - '0';
			}
			punteroCadena++;
		}

		descriptor[campoActual].desc = descCampo;
		descriptor[campoActual].modificador = modificador;
		campoActual++;

		modificador = 0;
	}

	return DescriptorRegistroFactory_Nuevo(descriptor, campoActual);
}
