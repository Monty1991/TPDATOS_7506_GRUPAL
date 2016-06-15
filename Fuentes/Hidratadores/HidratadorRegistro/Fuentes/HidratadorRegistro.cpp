#include "../Headers/HidratadorRegistro.h"
#include "../../HidratadorFeature/HidratadorFeatureFactory.h"
#include "../../HidratadorNumerico/HidratadorNumericoFactory.h"
#include "../../../Memoria/Registro/RegistroFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorRegistro::HidratadorRegistro()
{
	this->hidratadorNumerico = HidratadorNumericoFactory_Nuevo();
	this->hidratadorFeature = HidratadorFeatureFactory_Nuevo();
}

HidratadorRegistro::~HidratadorRegistro()
{
	if (this->hidratadorNumerico)
		this->hidratadorNumerico->Dispose();

	if (this->hidratadorFeature)
		this->hidratadorFeature->Dispose();
}

size_t HidratadorRegistro::Hidratar(char *buff, iRegistroPtr *registro)
{
	uNumber number;

	size_t cantidadLeida = this->hidratadorNumerico->Hidratar(buff, &number, eValueType_U1);
	
	size_t cantidadCampos = number.entero.enteroSinSigno.entero8SinSigno;
	iRegistroPtr nuevoRegistro = RegistroFactory_Nuevo(cantidadCampos);

	iFeaturePtr feature = NULL;
	for (size_t i = 0; i < cantidadCampos; i++)
	{
		cantidadLeida += this->hidratadorFeature->Hidratar(buff +cantidadLeida, &feature);
		Sistema_Execute(nuevoRegistro->SetFeature(i, feature););
	}

	*registro = nuevoRegistro;
	return cantidadLeida;
}

void HidratadorRegistro::Dispose()
{
	delete this;
}
