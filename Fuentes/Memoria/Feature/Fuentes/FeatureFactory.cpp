#include "../FeatureFactory.h"
#include "../Headers/Feature.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include <stdlib.h>

iFeaturePtr FeatureFactory_Nuevo(uValue valor, eValueType tipo)
{
	return new Feature(valor, tipo);
}

iFeaturePtr FeatureFactory_Nuevo(sCadenaANSI *cadena)
{
	return new Feature(cadena);
}

iFeaturePtr FeatureFactory_Nuevo(const sDescriptorCampoPtr descCampo, const char *cadena, char **cadenaSiguiente)
{
	if (!descCampo)
		Throw(ExceptionType_InvalidArg, "descCampo == NULL");
	if (!cadena)
		Throw(ExceptionType_InvalidArg, "cadena == NULL");

	char *nuevaCadena = (char *)cadena;
	iFeaturePtr feature = NULL;
	switch (descCampo->desc)
	{
		case eDescriptorCampo::eDescriptorCampo_U:
		{
			uValue value;
			unsigned INT64 valor = strtoull(cadena, &nuevaCadena, 0);
			
			if (descCampo->modificador < 9)
			{
				value.primitivo.numero.entero.enteroSinSigno.entero8SinSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_U1);
			}
			else if (descCampo->modificador < 17)
			{
				value.primitivo.numero.entero.enteroSinSigno.entero16SinSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_U2);
			}
			else if (descCampo->modificador < 33)
			{
				value.primitivo.numero.entero.enteroSinSigno.entero32SinSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_U4);
			}
			else
			{
				value.primitivo.numero.entero.enteroSinSigno.entero64SinSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_U8);
			}
		}
		break;

		case eDescriptorCampo::eDescriptorCampo_I:
		{
			uValue value;
			INT64 valor = strtoll(cadena, &nuevaCadena, 0);
			
			if (descCampo->modificador < 9)
			{
				value.primitivo.numero.entero.enteroConSigno.entero8ConSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_I1);
			}
			else if (descCampo->modificador < 17)
			{
				value.primitivo.numero.entero.enteroConSigno.entero16ConSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_I2);
			}
			else if (descCampo->modificador < 33)
			{
				value.primitivo.numero.entero.enteroConSigno.entero32ConSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_I4);
			}
			else
			{
				value.primitivo.numero.entero.enteroConSigno.entero64ConSigno = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_I8);
			}
		}
		break;

		case eDescriptorCampo::eDescriptorCampo_F:
		{
			uValue value;
			
			double valor = strtod(cadena, &nuevaCadena);
			
			if (descCampo->modificador < 33)
			{
				value.primitivo.numero.flotante.flotante32 = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_F32);
			}
			else
			{
				value.primitivo.numero.flotante.flotante64 = valor;
				feature = FeatureFactory_Nuevo(value, eValueType::eValueType_F64);
			}
		}
		break;

		case eDescriptorCampo::eDescriptorCampo_C:
		{
			sCadenaANSI cadenaANSI;
			cadenaANSI.cadena = (char *)cadena;

			size_t largoCadena = 0;
			while ((cadena[largoCadena] != ',') && (cadena[largoCadena] != ';') && (cadena[largoCadena] != '\n') && (cadena[largoCadena] != '\0'))
				largoCadena++;

			cadenaANSI.largo = largoCadena;

			feature = FeatureFactory_Nuevo(&cadenaANSI);
			nuevaCadena = (char *)cadena + largoCadena;
		}
		break;

		case eDescriptorCampo::eDescriptorCampo_CV:
		{
			sCadenaANSI cadenaANSI;
			cadenaANSI.cadena = (char *)cadena;

			size_t largoCadena = 0;
			while ((cadena[largoCadena] != ',') && (cadena[largoCadena] != ';') && (cadena[largoCadena] != '\n') && (cadena[largoCadena] != '\0'))
				largoCadena++;

			cadenaANSI.largo = largoCadena;

			feature = FeatureFactory_Nuevo(&cadenaANSI);
			nuevaCadena = (char *)cadena + largoCadena;
		}
		break;

		case eDescriptorCampo::eDescriptorCampo_Unknown:
		{
			Throw(ExceptionType_InvalidArg, "descCampo == eDescriptorCampo_Unknown");
		}
		break;
	}

	if (cadenaSiguiente)
		*cadenaSiguiente = nuevaCadena;

	return feature;
}
