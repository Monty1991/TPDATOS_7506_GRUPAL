#include "../DescriptorRegistroFactory.h"
#include "../Headers/DescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(const sDescriptorCampoPtr tablaDescriptorCampo, size_t cantidadDescriptoresCampo)
{
	return new DescriptorRegistro(tablaDescriptorCampo, cantidadDescriptoresCampo);
}

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(const char *cadenaDescriptorRegistro)
{
	size_t cuentaComas = 0;
	
	for (const char *i = cadenaDescriptorRegistro; *i != '\0'; i++)
		if (*i == ',')
			cuentaComas++;

	sDescriptorCampo descriptor[cuentaComas];
	size_t campoActual = 0;
	const char *punteroCadena = cadenaDescriptorRegistro;
	for (size_t i = 0; i < cuentaComas; i++)
	{
		if (*punteroCadena == '\0')
			break;

		if (*punteroCadena == ',')
			continue;

		eDescriptorCampo descCampo;
		switch (*punteroCadena)
		{
			case 'u': case 'U':
				descCampo = eDescriptorCampo::eDescriptorCampo_U;
				break;
			case 'i': case 'I':
				descCampo = eDescriptorCampo::eDescriptorCampo_I;
				break;
			case 'f': case 'F':
				descCampo = eDescriptorCampo::eDescriptorCampo_F;
				break;
			case 'c': case 'C':
				descCampo = eDescriptorCampo::eDescriptorCampo_C;
				break;
			case 'v': case 'V':
				descCampo = eDescriptorCampo::eDescriptorCampo_CV;
				break;

			default:
				// problemas
				// debiera lanzar excepcion
				return NULL;
		}

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

		modificador = 0;
	}

	return DescriptorRegistroFactory_Nuevo(descriptor, campoActual);
}
