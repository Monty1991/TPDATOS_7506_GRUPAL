#include "../Headers/SerializadorFeature.h"

#include "../../SerializadorCadenaANSI/SerializadorCadenaANSIFactory.h"
#include "../../SerializadorCadenaUNICODE/SerializadorCadenaUNICODEFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"

SerializadorFeature::SerializadorFeature()
{
	this->serializadorCadenaANSI = SerializadorCadenaANSIFactory_Nuevo();
	this->serializadorCadenaUNICODE = SerializadorCadenaUNICODEFactory_Nuevo();
}

SerializadorFeature::~SerializadorFeature()
{
	if (this->serializadorCadenaANSI)
		this->serializadorCadenaANSI->Dispose();

	if (this->serializadorCadenaUNICODE)
		this->serializadorCadenaUNICODE->Dispose();
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
		Sistema_Execute(espacio += this->serializadorCadenaUNICODE->CalcularEspacio(feature->AsCadenaUNICODE()););
	else
		Sistema_Execute(espacio += this->serializadorCadenaANSI->CalcularEspacio(feature->AsCadenaANSI()););

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
		Sistema_Execute(escrito += this->serializadorCadenaUNICODE->Serializar(buffer + escrito, feature->AsCadenaUNICODE()););
	else
		Sistema_Execute(escrito += this->serializadorCadenaANSI->Serializar(buffer + escrito, feature->AsCadenaANSI()););

	return escrito;
}

void SerializadorFeature::Dispose()
{
	delete this;
}
