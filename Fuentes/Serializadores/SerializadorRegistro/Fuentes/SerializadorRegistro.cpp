#include "../Headers/SerializadorRegistro.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

SerializadorRegistro::SerializadorRegistro()
{
}

SerializadorRegistro::~SerializadorRegistro()
{
}

size_t SerializadorRegistro::CalcularEspacio(const iRegistroPtr registro)
{
	if (!registro)
		Throw(ExceptionType_InvalidArg, "registro == NULL");

	size_t espacio = 0;
	size_t cantCampos = registro->ObtenerCantidadCampos();
	
	Sistema_Execute(espacio += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U1););

	for (size_t i = 0; i < cantCampos; i++)
		Sistema_Execute(espacio += FeatureFactory_CalcularEspacioSerializacion(registro->GetFeature(i)););

	return espacio;
}

size_t SerializadorRegistro::Serializar(char *buffer, const iRegistroPtr registro)
{
	if (!registro)
		Throw(ExceptionType_InvalidArg, "registro == NULL");

	size_t cantidadEscrita = 0;
	size_t cantCampos = registro->ObtenerCantidadCampos();

	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = cantCampos;
	Sistema_Execute(cantidadEscrita += NumberUtils_Serializar(buffer + cantidadEscrita, number, eValueType::eValueType_U1););

	for (size_t i = 0; i < cantCampos; i++)
		Sistema_Execute(cantidadEscrita += FeatureFactory_Serializar(buffer + cantidadEscrita, registro->GetFeature(i)););

	return cantidadEscrita;
}

void SerializadorRegistro::Dispose()
{
	delete this;
}
