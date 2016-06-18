#include "../Headers/HidratadorCadenaANSI.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../HidratadorCadenaSinPrefijo/HidratadorCadenaSinPrefijoFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorCadenaANSI::HidratadorCadenaANSI()
{
	this->hidratadorCadenaSinPrefijo = HidratadorCadenaSinPrefijoFactory_Nuevo();
}

HidratadorCadenaANSI::~HidratadorCadenaANSI()
{
	if (this->hidratadorCadenaSinPrefijo)
		this->hidratadorCadenaSinPrefijo->Dispose();
}
		
size_t HidratadorCadenaANSI::Hidratar(char *buff, sCadenaANSI *cadena)
{
	uNumber largo;
	largo.entero.enteroSinSigno.entero64SinSigno = 0;
	size_t leido = 0;

	Sistema_Execute(leido = NumberUtils_Hidratar(buff + leido, &largo, eValueType::eValueType_U2););
	size_t largoCadena = largo.entero.enteroSinSigno.entero16SinSigno;

	cadena->cadena = new char[largoCadena];
	cadena->largo = largoCadena;

	Sistema_Execute(leido += this->hidratadorCadenaSinPrefijo->Hidratar(buff + leido, cadena->cadena, largoCadena););

	return leido;
}

void HidratadorCadenaANSI::Dispose()
{
	delete this;
}
