#include "../Headers/SerializadorCadenaUNICODE.h"
#include "../../SerializadorNumerico/SerializadorNumericoFactory.h"
#include "../../SerializadorCadenaSinPrefijo/SerializadorCadenaSinPrefijoFactory.h"

SerializadorCadenaUNICODE::SerializadorCadenaUNICODE()
{
	this->serializadorNumerico = SerializadorNumericoFactory_Nuevo();
	this->serializadorCadenaSinPrefijo = SerializadorCadenaSinPrefijoFactory_Nuevo();
}

SerializadorCadenaUNICODE::~SerializadorCadenaUNICODE()
{
	if (this->serializadorNumerico)
		this->serializadorNumerico->Dispose();

	if (this->serializadorCadenaSinPrefijo)
		this->serializadorCadenaSinPrefijo->Dispose();
}

size_t SerializadorCadenaUNICODE::CalcularEspacio(sCadenaUNICODE *cadena)
{
	uNumber largo;
	largo.entero.enteroSinSigno.entero16SinSigno = cadena->largo;

	size_t espacioSerializacion = this->serializadorNumerico->CalcularEspacio(largo, eValueType::eValueType_U2)
			+ this->serializadorCadenaSinPrefijo->CalcularEspacio((char *)(cadena->cadena), cadena->largo * sizeof(wchar_t));

	return espacioSerializacion;
}

size_t SerializadorCadenaUNICODE::Serializar(char *buff, sCadenaUNICODE *cadena)
{
	size_t espacioSerializacion = this->CalcularEspacio(cadena);

	uNumber largo;
	largo.entero.enteroSinSigno.entero16SinSigno = cadena->largo;
	buff += this->serializadorNumerico->Serializar(buff, largo, eValueType::eValueType_U2);
	this->serializadorCadenaSinPrefijo->Serializar(buff, (char *)(cadena->cadena), cadena->largo * sizeof(wchar_t));

	return espacioSerializacion;
}

void SerializadorCadenaUNICODE::Dispose()
{
	delete this;
}