#include "../RegistroFactory.h"
#include "../Headers/Registro.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../Feature/FeatureFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

iRegistroPtr RegistroFactory_Nuevo(size_t cantidadCampos)
{
	return new Registro(cantidadCampos);
}

iRegistroPtr RegistroFactory_Nuevo(iDescriptorRegistroPtr descriptor, const char *cadena)
{
	if (!descriptor || !cadena)
		return NULL;

	iRegistroPtr registro = RegistroFactory_Nuevo(descriptor->ObtenerCantidadCampos());
	char *cadenaRegistro = (char *)cadena;
	iFeaturePtr campo = NULL;
	for (size_t i = 0; i < descriptor->ObtenerCantidadCampos(); i++)
	{
		Sistema_Execute(campo = FeatureFactory_Nuevo(descriptor->ObtenerDescriptorCampo(i), cadenaRegistro, &cadenaRegistro););
		Sistema_Execute(registro->SetFeature(i, campo););

		// llegados aquí, se leyo hasta la coma
		cadenaRegistro++;
	}

	return registro;
}

size_t RegistroFactory_CalcularEspacioSerializacion(const iRegistroPtr registro)
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

size_t RegistroFactory_Serializar(char *buffer, const iRegistroPtr registro)
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

size_t RegistroFactory_Hidratar(const char *buff, iRegistroPtr *registro)
{
	uNumber number;
	number.entero.enteroSinSigno.entero64SinSigno = 0;

	size_t cantidadLeida = 0;
	Sistema_Execute(cantidadLeida += NumberUtils_Hidratar(buff + cantidadLeida, &number, eValueType_U1););
	
	size_t cantidadCampos = number.entero.enteroSinSigno.entero8SinSigno;
	iRegistroPtr nuevoRegistro = RegistroFactory_Nuevo(cantidadCampos);

	iFeaturePtr feature = NULL;
	for (size_t i = 0; i < cantidadCampos; i++)
	{
		Sistema_Execute(cantidadLeida += FeatureFactory_Hidratar(buff + cantidadLeida, &feature););
		Sistema_Execute(nuevoRegistro->SetFeature(i, feature););
	}

	*registro = nuevoRegistro;
	return cantidadLeida;
}
