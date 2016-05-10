#include "../Headers/SerializadorRegistro.h"
#include "../../SerializadorFeature/SerializadorFeatureFactory.h"

SerializadorRegistro::SerializadorRegistro()
{
	this->serializadorFeature = SerializadorFeatureFactory_Nuevo();
}

SerializadorRegistro::~SerializadorRegistro()
{
	if (this->serializadorFeature)
		this->serializadorFeature->Dispose();
}

size_t SerializadorRegistro::CalcularEspacio(const iRegistroPtr registro)
{
	size_t cantCampos = registro->ObtenerCantidadCampos();
	size_t espacio = 0;
	for (size_t i = 0; i < cantCampos; i++)
		espacio += this->serializadorFeature->CalcularEspacio(registro->GetFeature(i));

	return espacio;
}

size_t SerializadorRegistro::Serializar(char *buffer, const iRegistroPtr registro)
{
	size_t cantCampos = registro->ObtenerCantidadCampos();
	size_t cantidadEscrita = 0;
	for (size_t i = 0; i < cantCampos; i++)
		cantidadEscrita += this->serializadorFeature->Serializar(buffer + cantidadEscrita, registro->GetFeature(i));

	return cantidadEscrita;
}

void SerializadorRegistro::Dispose()
{
	delete this;
}
