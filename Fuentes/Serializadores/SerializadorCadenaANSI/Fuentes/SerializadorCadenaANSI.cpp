#include "../Headers/SerializadorCadenaANSI.h"
#include "../../SerializadorCadenaSinPrefijo/SerializadorCadenaSinPrefijoFactory.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

SerializadorCadenaANSI::SerializadorCadenaANSI()
{
	this->serializadorCadenaSinPrefijo = SerializadorCadenaSinPrefijoFactory_Nuevo();
}

SerializadorCadenaANSI::~SerializadorCadenaANSI()
{
	if (this->serializadorCadenaSinPrefijo)
		this->serializadorCadenaSinPrefijo->Dispose();
}
	
size_t SerializadorCadenaANSI::CalcularEspacio(sCadenaANSI *cadena)
{
	size_t espacioSerializacion = 0;
	Sistema_Execute(espacioSerializacion += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U2););
	Sistema_Execute(espacioSerializacion += this->serializadorCadenaSinPrefijo->CalcularEspacio(cadena->cadena, cadena->largo););

	return espacioSerializacion;
}

size_t SerializadorCadenaANSI::Serializar(char *buff, sCadenaANSI *cadena)
{
	size_t espacioSerializacion = 0;

	uNumber largo;
	largo.entero.enteroSinSigno.entero16SinSigno = cadena->largo;
	Sistema_Execute(espacioSerializacion += NumberUtils_Serializar(buff + espacioSerializacion, largo, eValueType::eValueType_U2););
	Sistema_Execute(espacioSerializacion += this->serializadorCadenaSinPrefijo->Serializar(buff + espacioSerializacion, cadena->cadena, cadena->largo););

	return espacioSerializacion;
}

void SerializadorCadenaANSI::Dispose()
{
	delete this;
}
