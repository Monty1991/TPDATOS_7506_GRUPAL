#include "../FeatureFactory.h"
#include "../Headers/Feature.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"
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
			value.primitivo.numero.entero.enteroSinSigno.entero64SinSigno = 0;
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
			value.primitivo.numero.entero.enteroConSigno.entero64ConSigno = 0;
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

size_t FeatureFactory_CalcularEspacioSerializacion(const iFeaturePtr feature)
{
	if (!feature)
		Throw(ExceptionType_InvalidArg, "feature == NULL");

	eValueType tipo = feature->ObtenerTipo();

	size_t espacio = 0;
	Sistema_Execute(espacio += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U1););

	if (tipo & Mascara_Numero)
		Sistema_Execute(espacio += NumberUtils_CalcularEspacioSerializacion(tipo););
	else if (tipo & Mascara_Unicode)
		Sistema_Execute(espacio += StringUtils_CalcularEspacioSerializacion(feature->AsCadenaUNICODE()););
	else
		Sistema_Execute(espacio += StringUtils_CalcularEspacioSerializacion(feature->AsCadenaANSI()););

	return espacio;
}

size_t FeatureFactory_Serializar(char *buffer, const iFeaturePtr feature)
{
	if (!feature)
		Throw(ExceptionType_InvalidArg, "feature == NULL");

	eValueType tipo = feature->ObtenerTipo();

	size_t escrito = 0;
	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = tipo;
	Sistema_Execute(escrito += NumberUtils_Serializar(buffer + escrito, number, eValueType::eValueType_U1););

	if (tipo & Mascara_Numero)
		Sistema_Execute(escrito += NumberUtils_Serializar(buffer + escrito, feature->AsNumber(), tipo););
	else if (tipo & Mascara_Unicode)
		Sistema_Execute(escrito += StringUtils_Serializar(buffer + escrito, feature->AsCadenaUNICODE()););
	else
		Sistema_Execute(escrito += StringUtils_Serializar(buffer + escrito, feature->AsCadenaANSI()););

	return escrito;
}

size_t FeatureFactory_Hidratar(const char *buff, iFeaturePtr *feature)
{
	uValue valor;
	valor.primitivo.numero.entero.enteroSinSigno.entero64SinSigno = 0;
	size_t leido = 0;
	
	Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &valor.primitivo.numero, eValueType_U1););

	eValueType tipo = (eValueType) valor.primitivo.numero.entero.enteroSinSigno.entero8SinSigno;

	iFeaturePtr featureLeido = NULL;
	valor.primitivo.numero.entero.enteroSinSigno.entero64SinSigno = 0;
	if (tipo & Mascara_Numero)
	{
		Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &(valor.primitivo.numero), tipo););
		featureLeido = FeatureFactory_Nuevo(valor, tipo);
	}
	else if (tipo & Mascara_Unicode)
	{
		Sistema_Execute(leido += StringUtils_Hidratar(buff + leido, &(valor.primitivo.cadena.unicode)););
		featureLeido = FeatureFactory_Nuevo(valor, tipo);
		delete [] valor.primitivo.cadena.unicode.cadena;
	}
	else
	{
		Sistema_Execute(leido += StringUtils_Hidratar(buff + leido, &(valor.primitivo.cadena.ansi)););
		featureLeido = FeatureFactory_Nuevo(&valor.primitivo.cadena.ansi);
		delete [] valor.primitivo.cadena.ansi.cadena;
	}
	*feature = featureLeido;

	return leido;
}
