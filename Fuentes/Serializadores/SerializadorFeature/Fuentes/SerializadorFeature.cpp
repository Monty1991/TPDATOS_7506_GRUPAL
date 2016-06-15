#include "../Headers/SerializadorFeature.h"

#include "../../SerializadorNumerico/SerializadorNumericoFactory.h"
#include "../../SerializadorCadenaANSI/SerializadorCadenaANSIFactory.h"
#include "../../SerializadorCadenaUNICODE/SerializadorCadenaUNICODEFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"
#include "../../../Exceptions/ExceptionFactory.h"

SerializadorFeature::SerializadorFeature()
{
	this->serializadorNumerico = SerializadorNumericoFactory_Nuevo();
	this->serializadorCadenaANSI = SerializadorCadenaANSIFactory_Nuevo();
	this->serializadorCadenaUNICODE = SerializadorCadenaUNICODEFactory_Nuevo();
}

SerializadorFeature::~SerializadorFeature()
{
	if (this->serializadorNumerico)
		this->serializadorNumerico->Dispose();

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

	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = tipo;
	size_t espacio = this->serializadorNumerico->CalcularEspacio(number, eValueType::eValueType_U1);

	if (tipo & Mascara_Numero)
		return espacio + this->serializadorNumerico->CalcularEspacio(feature->AsNumber(), tipo);

	if (tipo & Mascara_Unicode)
		return espacio + this->serializadorCadenaUNICODE->CalcularEspacio(feature->AsCadenaUNICODE());

	return espacio + this->serializadorCadenaANSI->CalcularEspacio(feature->AsCadenaANSI());
}

size_t SerializadorFeature::Serializar(char *buffer, const iFeaturePtr feature)
{
	if (!feature)
		Throw(ExceptionType_InvalidArg, "feature == NULL");

	eValueType tipo = feature->ObtenerTipo();

	size_t escrito = 0;
	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = tipo;
	escrito += this->serializadorNumerico->Serializar(buffer + escrito, number, eValueType::eValueType_U1);

	if (tipo & Mascara_Numero)
		Sistema_Execute(escrito += this->serializadorNumerico->Serializar(buffer + escrito, feature->AsNumber(), tipo););
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
