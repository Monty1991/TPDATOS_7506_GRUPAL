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
	eValueType tipo = feature->ObtenerTipo();

	if (tipo & Mascara_Numero)
		return this->serializadorNumerico->CalcularEspacio(feature->AsNumber(), tipo);

	if (tipo & Mascara_Unicode)
		return this->serializadorCadenaUNICODE->CalcularEspacio(feature->AsCadenaUNICODE());

	return this->serializadorCadenaANSI->CalcularEspacio(feature->AsCadenaANSI());
}

size_t SerializadorFeature::Serializar(char *buffer, const iFeaturePtr feature)
{
	eValueType tipo = feature->ObtenerTipo();

	if (tipo & Mascara_Numero)
		return this->serializadorNumerico->Serializar(buffer, feature->AsNumber(), tipo);

	if (tipo & Mascara_Unicode)
		return this->serializadorCadenaUNICODE->Serializar(buffer, feature->AsCadenaUNICODE());

	return this->serializadorCadenaANSI->Serializar(buffer, feature->AsCadenaANSI());	
}

void SerializadorFeature::Dispose()
{
	delete this;
}
