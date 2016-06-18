#include "../Headers/SerializadorFeature.h"

#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"
#include "../../../Exceptions/ExceptionFactory.h"

SerializadorFeature::SerializadorFeature()
{
}

SerializadorFeature::~SerializadorFeature()
{
}

size_t SerializadorFeature::CalcularEspacio(const iFeaturePtr feature)
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

size_t SerializadorFeature::Serializar(char *buffer, const iFeaturePtr feature)
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

void SerializadorFeature::Dispose()
{
	delete this;
}
