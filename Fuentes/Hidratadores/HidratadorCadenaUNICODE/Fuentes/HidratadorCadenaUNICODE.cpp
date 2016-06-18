#include "../Headers/HidratadorCadenaUNICODE.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../HidratadorCadenaSinPrefijo/HidratadorCadenaSinPrefijoFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorCadenaUNICODE::HidratadorCadenaUNICODE()
{
	this->hidratadorCadenaSinPrefijo = HidratadorCadenaSinPrefijoFactory_Nuevo();
}

HidratadorCadenaUNICODE::~HidratadorCadenaUNICODE()
{
	if (this->hidratadorCadenaSinPrefijo)
		this->hidratadorCadenaSinPrefijo->Dispose();
}

size_t HidratadorCadenaUNICODE::Hidratar(char *buff, sCadenaUNICODE *cadena)
{
	uNumber largo;
	largo.entero.enteroSinSigno.entero64SinSigno = 0;
	size_t leido = 0;

	Sistema_Execute(leido = NumberUtils_Hidratar(buff + leido, &largo, eValueType::eValueType_U2););
	size_t largoCadena = largo.entero.enteroSinSigno.entero16SinSigno;

	cadena->cadena = new wchar_t[largoCadena];
	cadena->largo = largoCadena;

	Sistema_Execute(leido += this->hidratadorCadenaSinPrefijo->Hidratar(buff + leido, (char *)(cadena->cadena), largoCadena * sizeof(wchar_t)););

	return leido;
}

void HidratadorCadenaUNICODE::Dispose()
{
	delete this;
}
