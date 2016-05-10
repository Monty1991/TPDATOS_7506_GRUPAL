#include "../Headers/HidratadorFeature.h"
#include "../../HidratadorNumerico/HidratadorNumericoFactory.h"
#include "../../HidratadorCadenaANSI/HidratadorCadenaANSIFactory.h"
#include "../../HidratadorCadenaUNICODE/HidratadorCadenaUNICODEFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"

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

size_t HidratadorFeature::Hidratar(char *buff, iFeaturePtr *feature, eValueType tipo)
{
	uValue valor;

	if (tipo & Mascara_Numero)
		this->hidratadorNumerico->Hidratar(buff, &(valor.primitivo.numero), tipo);
	else if (tipo & Mascara_Unicode)
		this->hidratadorCadenaUNICODE->Hidratar(buff, &(valor.primitivo.cadena.unicode));
	else
		this->hidratadorCadenaANSI->Hidratar(buff, &(valor.primitivo.cadena.ansi));

	*feature = FeatureFactory_Nuevo(valor, tipo);
}

void HidratadorFeature::Dispose()
{
	delete this;
}
