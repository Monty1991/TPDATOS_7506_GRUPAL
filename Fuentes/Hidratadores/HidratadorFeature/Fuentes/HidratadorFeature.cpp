#include "../Headers/HidratadorFeature.h"
#include "../../HidratadorNumerico/HidratadorNumericoFactory.h"
#include "../../HidratadorCadenaANSI/HidratadorCadenaANSIFactory.h"
#include "../../HidratadorCadenaUNICODE/HidratadorCadenaUNICODEFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorFeature::HidratadorFeature()
{
	this->hidratadorNumerico = HidratadorNumericoFactory_Nuevo();
	this->hidratadorCadenaANSI = HidratadorCadenaANSIFactory_Nuevo();
	this->hidratadorCadenaUNICODE = HidratadorCadenaUNICODEFactory_Nuevo();
}

HidratadorFeature::~HidratadorFeature()
{
	if (this->hidratadorNumerico)
		this->hidratadorNumerico->Dispose();

	if (this->hidratadorCadenaANSI)
		this->hidratadorCadenaANSI->Dispose();

	if (this->hidratadorCadenaUNICODE)
		this->hidratadorCadenaUNICODE->Dispose();
}

size_t HidratadorFeature::Hidratar(char *buff, iFeaturePtr *feature)
{
	uNumber number;
	size_t leido = 0;
	
	Sistema_Execute(leido += this->hidratadorNumerico->Hidratar(buff, &number, eValueType_U1););

	eValueType tipo = (eValueType) number.entero.enteroSinSigno.entero8SinSigno;
	uValue valor;

	if (tipo & Mascara_Numero)
		Sistema_Execute(leido += this->hidratadorNumerico->Hidratar(buff, &(valor.primitivo.numero), tipo););
	else if (tipo & Mascara_Unicode)
		Sistema_Execute(leido += this->hidratadorCadenaUNICODE->Hidratar(buff, &(valor.primitivo.cadena.unicode)););
	else
		Sistema_Execute(leido += this->hidratadorCadenaANSI->Hidratar(buff, &(valor.primitivo.cadena.ansi)););

	*feature = FeatureFactory_Nuevo(valor, tipo);

	return leido;
}

void HidratadorFeature::Dispose()
{
	delete this;
}
