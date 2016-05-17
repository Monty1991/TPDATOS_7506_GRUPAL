#include "../Headers/SerializadorRegistro.h"
#include "../../SerializadorFeature/SerializadorFeatureFactory.h"
#include "../../SerializadorNumerico/SerializadorNumericoFactory.h"

SerializadorRegistro::SerializadorRegistro()
{
	this->serializadorNumerico = SerializadorNumericoFactory_Nuevo();
	this->serializadorFeature = SerializadorFeatureFactory_Nuevo();
}

SerializadorRegistro::~SerializadorRegistro()
{
	if (this->serializadorNumerico)
		this->serializadorNumerico->Dispose();

	if (this->serializadorFeature)
		this->serializadorFeature->Dispose();
}

size_t SerializadorRegistro::CalcularEspacio(const iRegistroPtr registro)
{
	size_t cantCampos = registro->ObtenerCantidadCampos();
	
	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = cantCampos;
	size_t espacio = this->serializadorNumerico->CalcularEspacio(number, eValueType_U1);
	for (size_t i = 0; i < cantCampos; i++)
		espacio += this->serializadorFeature->CalcularEspacio(registro->GetFeature(i));

	return espacio;
}

size_t SerializadorRegistro::Serializar(char *buffer, const iRegistroPtr registro)
{
	size_t cantCampos = registro->ObtenerCantidadCampos();
	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = cantCampos;
	size_t cantidadEscrita = this->serializadorNumerico->Serializar(buffer, number, eValueType_U1);
	for (size_t i = 0; i < cantCampos; i++)
		cantidadEscrita += this->serializadorFeature->Serializar(buffer + cantidadEscrita, registro->GetFeature(i));

	return cantidadEscrita;
}

void SerializadorRegistro::Dispose()
{
	delete this;
}
