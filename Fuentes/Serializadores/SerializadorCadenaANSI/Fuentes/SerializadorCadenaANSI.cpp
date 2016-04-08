#include "../Headers/SerializadorCadenaANSI.h"
#include "../../SerializadorNumerico/SerializadorNumericoFactory.h"
#include "../../SerializadorCadenaSinPrefijo/SerializadorCadenaSinPrefijoFactory.h"

SerializadorCadenaANSI::SerializadorCadenaANSI()
{
	this->serializadorNumerico = SerializadorNumericoFactory_Nuevo();
	this->serializadorCadenaSinPrefijo = SerializadorCadenaSinPrefijoFactory_Nuevo();
}

SerializadorCadenaANSI::~SerializadorCadenaANSI()
{
	if (this->serializadorNumerico)
		this->serializadorNumerico->Dispose();

	if (this->serializadorCadenaSinPrefijo)
		this->serializadorCadenaSinPrefijo->Dispose();
}
	
size_t SerializadorCadenaANSI::CalcularEspacio(sCadenaANSI *cadena)
{
	uNumber largo;
	largo.entero.enteroSinSigno.entero8SinSigno = cadena->largo;
	
	size_t espacioSerializacion = this->serializadorNumerico->CalcularEspacio(largo, eValueType::eValueType_U8)
			+ this->serializadorCadenaSinPrefijo->CalcularEspacio(cadena->cadena, cadena->largo);

	return espacioSerializacion;
}

size_t SerializadorCadenaANSI::Serializar(char *buff, sCadenaANSI *cadena)
{
	size_t espacioSerializacion = this->CalcularEspacio(cadena);

	uNumber largo;
	largo.entero.enteroSinSigno.entero8SinSigno = cadena->largo;
	buff += this->serializadorNumerico->Serializar(buff, largo, eValueType::eValueType_U8);
	this->serializadorCadenaSinPrefijo->Serializar(buff, cadena->cadena, cadena->largo);

	return espacioSerializacion;
}

void SerializadorCadenaANSI::Dispose()
{
	delete this;
}
