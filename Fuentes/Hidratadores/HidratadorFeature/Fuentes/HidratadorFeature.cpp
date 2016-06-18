#include "../Headers/HidratadorFeature.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../HidratadorCadenaANSI/HidratadorCadenaANSIFactory.h"
#include "../../HidratadorCadenaUNICODE/HidratadorCadenaUNICODEFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorFeature::HidratadorFeature()
{
	this->hidratadorCadenaANSI = HidratadorCadenaANSIFactory_Nuevo();
	this->hidratadorCadenaUNICODE = HidratadorCadenaUNICODEFactory_Nuevo();
}

HidratadorFeature::~HidratadorFeature()
{
	if (this->hidratadorCadenaANSI)
		this->hidratadorCadenaANSI->Dispose();

	if (this->hidratadorCadenaUNICODE)
		this->hidratadorCadenaUNICODE->Dispose();
}

size_t HidratadorFeature::Hidratar(char *buff, iFeaturePtr *feature)
{
	uNumber number;
	number.entero.enteroSinSigno.entero64SinSigno = 0;
	size_t leido = 0;
	
	Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &number, eValueType_U1););

	eValueType tipo = (eValueType) number.entero.enteroSinSigno.entero8SinSigno;
	uValue valor;

	// limpiamos por las dudas
	valor.primitivo.numero.entero.enteroSinSigno.entero64SinSigno = 0;

	iFeaturePtr featureLeido = NULL;
	if (tipo & Mascara_Numero)
	{
		Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &(valor.primitivo.numero), tipo););
		featureLeido = FeatureFactory_Nuevo(valor, tipo);
	}
	else if (tipo & Mascara_Unicode)
	{
		Sistema_Execute(leido += this->hidratadorCadenaUNICODE->Hidratar(buff + leido, &(valor.primitivo.cadena.unicode)););
		featureLeido = FeatureFactory_Nuevo(valor, tipo);
		delete [] valor.primitivo.cadena.unicode.cadena;
	}
	else
	{
		Sistema_Execute(leido += this->hidratadorCadenaANSI->Hidratar(buff + leido, &(valor.primitivo.cadena.ansi)););
		featureLeido = FeatureFactory_Nuevo(valor, tipo);
		delete [] valor.primitivo.cadena.ansi.cadena;
	}
	*feature = featureLeido;

	return leido;
}

void HidratadorFeature::Dispose()
{
	delete this;
}
