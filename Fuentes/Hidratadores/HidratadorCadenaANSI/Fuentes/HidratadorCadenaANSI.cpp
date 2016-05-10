#include "../Headers/HidratadorCadenaANSI.h"
#include "../../HidratadorNumerico/HidratadorNumericoFactory.h"
#include "../../HidratadorCadenaSinPrefijo/HidratadorCadenaSinPrefijoFactory.h"

HidratadorCadenaANSI::HidratadorCadenaANSI()
{
	this->hidratadorNumerico = HidratadorNumericoFactory_Nuevo();
	this->hidratadorCadenaSinPrefijo = HidratadorCadenaSinPrefijoFactory_Nuevo();
}

HidratadorCadenaANSI::~HidratadorCadenaANSI()
{
	if (this->hidratadorNumerico)
		this->hidratadorNumerico->Dispose();

	if (this->hidratadorCadenaSinPrefijo)
		this->hidratadorCadenaSinPrefijo->Dispose();
}
		
size_t HidratadorCadenaANSI::Hidratar(char *buff, sCadenaANSI *cadena)
{
	uNumber largo;
	size_t largoPrefijo = this->hidratadorNumerico->Hidratar(buff, &largo, eValueType::eValueType_U2);
	buff += largoPrefijo;

	size_t largoCadena = largo.entero.enteroSinSigno.entero16SinSigno;

	cadena->cadena = new char[largoCadena];
	cadena->largo = largoCadena;

	size_t largoCadenaLeido = this->hidratadorCadenaSinPrefijo->Hidratar(buff, cadena->cadena, largoCadena);

	return largoPrefijo + largoCadenaLeido;
}

void HidratadorCadenaANSI::Dispose()
{
	delete this;
}
