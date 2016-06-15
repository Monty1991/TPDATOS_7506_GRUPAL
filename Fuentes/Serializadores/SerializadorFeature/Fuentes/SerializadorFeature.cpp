#include "../Headers/SerializadorFeature.h"

#include "../../SerializadorNumerico/SerializadorNumericoFactory.h"
#include "../../SerializadorCadenaANSI/SerializadorCadenaANSIFactory.h"
#include "../../SerializadorCadenaUNICODE/SerializadorCadenaUNICODEFactory.h"

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
		return 0;

	eValueType tipo = feature->ObtenerTipo();

	uNumber number;
	size_t espacio = this->serializadorNumerico->CalcularEspacio(number, eValueType_U1);

	if (tipo & Mascara_Numero)
		return espacio + this->serializadorNumerico->CalcularEspacio(feature->AsNumber(), tipo);

	if (tipo & Mascara_Unicode)
		return espacio + this->serializadorCadenaUNICODE->CalcularEspacio(feature->AsCadenaUNICODE());

	return espacio + this->serializadorCadenaANSI->CalcularEspacio(feature->AsCadenaANSI());
}

size_t SerializadorFeature::Serializar(char *buffer, const iFeaturePtr feature)
{
	if (!feature)
		return 0;

	eValueType tipo = feature->ObtenerTipo();

	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = tipo;
	size_t escrito = this->serializadorNumerico->Serializar(buffer, number, eValueType_U1);

	if (tipo & Mascara_Numero)
		return escrito + this->serializadorNumerico->Serializar(buffer, feature->AsNumber(), tipo);

	if (tipo & Mascara_Unicode)
		return escrito + this->serializadorCadenaUNICODE->Serializar(buffer, feature->AsCadenaUNICODE());

	return escrito + this->serializadorCadenaANSI->Serializar(buffer, feature->AsCadenaANSI());	
}

void SerializadorFeature::Dispose()
{
	delete this;
}
