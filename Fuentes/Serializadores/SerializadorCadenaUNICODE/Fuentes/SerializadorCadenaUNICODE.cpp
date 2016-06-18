#include "../Headers/SerializadorCadenaUNICODE.h"
#include "../../SerializadorCadenaSinPrefijo/SerializadorCadenaSinPrefijoFactory.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

SerializadorCadenaUNICODE::SerializadorCadenaUNICODE()
{
	this->serializadorCadenaSinPrefijo = SerializadorCadenaSinPrefijoFactory_Nuevo();
}

SerializadorCadenaUNICODE::~SerializadorCadenaUNICODE()
{
	if (this->serializadorCadenaSinPrefijo)
		this->serializadorCadenaSinPrefijo->Dispose();
}

size_t SerializadorCadenaUNICODE::CalcularEspacio(sCadenaUNICODE *cadena)
{
	size_t espacioSerializacion = 0;

	Sistema_Execute(espacioSerializacion += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U2););
	Sistema_Execute(espacioSerializacion += this->serializadorCadenaSinPrefijo->CalcularEspacio((char *)(cadena->cadena), cadena->largo * sizeof(wchar_t)););

	return espacioSerializacion;
}

size_t SerializadorCadenaUNICODE::Serializar(char *buff, sCadenaUNICODE *cadena)
{
	size_t espacioSerializacion = 0;

	uNumber largo;
	largo.entero.enteroSinSigno.entero16SinSigno = cadena->largo;
	Sistema_Execute(espacioSerializacion += NumberUtils_Serializar(buff + espacioSerializacion, largo, eValueType::eValueType_U2););
	Sistema_Execute(espacioSerializacion += this->serializadorCadenaSinPrefijo->Serializar(buff + espacioSerializacion, (char *)(cadena->cadena), cadena->largo * sizeof(wchar_t)););

	return espacioSerializacion;
}

void SerializadorCadenaUNICODE::Dispose()
{
	delete this;
}
