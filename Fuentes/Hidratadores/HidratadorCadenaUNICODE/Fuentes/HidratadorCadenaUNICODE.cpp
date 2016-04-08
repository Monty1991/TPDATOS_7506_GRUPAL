#include "../Headers/HidratadorCadenaUNICODE.h"
#include "../../HidratadorNumerico/HidratadorNumericoFactory.h"
#include "../../HidratadorCadenaSinPrefijo/HidratadorCadenaSinPrefijoFactory.h"

HidratadorCadenaUNICODE::HidratadorCadenaUNICODE()
{
	this->hidratadorNumerico = HidratadorNumericoFactory_Nuevo();
	this->hidratadorCadenaSinPrefijo = HidratadorCadenaSinPrefijoFactory_Nuevo();
}

HidratadorCadenaUNICODE::~HidratadorCadenaUNICODE()
{
	if (this->hidratadorNumerico)
		this->hidratadorNumerico->Dispose();

	if (this->hidratadorCadenaSinPrefijo)
		this->hidratadorCadenaSinPrefijo->Dispose();
}

size_t HidratadorCadenaUNICODE::Hidratar(char *buff, sCadenaUNICODE **cadena)
{
	uNumber largo;
	size_t largoPrefijo = this->hidratadorNumerico->Hidratar(buff, &largo, eValueType::eValueType_U2);
	buff += largoPrefijo;

	size_t largoCadena = largo.entero.enteroSinSigno.entero16SinSigno;

	*cadena = new sCadenaUNICODE();
	(*cadena)->cadena = new wchar_t[largoCadena];
	(*cadena)->largo = largoCadena;

	size_t largoCadenaLeido = this->hidratadorCadenaSinPrefijo->Hidratar(buff, (char *)((*cadena)->cadena), largoCadena * sizeof(wchar_t));
	
	return largoPrefijo + largoCadenaLeido;	
}

void HidratadorCadenaUNICODE::Dispose()
{
	delete this;
}
