#include "../Headers/HidratadorRegistro.h"
#include "../../HidratadorFeature/HidratadorFeatureFactory.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Memoria/Registro/RegistroFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorRegistro::HidratadorRegistro()
{
	this->hidratadorFeature = HidratadorFeatureFactory_Nuevo();
}

HidratadorRegistro::~HidratadorRegistro()
{
	if (this->hidratadorFeature)
		this->hidratadorFeature->Dispose();
}

size_t HidratadorRegistro::Hidratar(char *buff, iRegistroPtr *registro)
{
	uNumber number;
	number.entero.enteroSinSigno.entero64SinSigno = 0;

	size_t cantidadLeida = 0;
	Sistema_Execute(cantidadLeida += NumberUtils_Hidratar(buff + cantidadLeida, &number, eValueType_U1););
	
	size_t cantidadCampos = number.entero.enteroSinSigno.entero8SinSigno;
	iRegistroPtr nuevoRegistro = RegistroFactory_Nuevo(cantidadCampos);

	iFeaturePtr feature = NULL;
	for (size_t i = 0; i < cantidadCampos; i++)
	{
		Sistema_Execute(cantidadLeida += this->hidratadorFeature->Hidratar(buff + cantidadLeida, &feature););
		Sistema_Execute(nuevoRegistro->SetFeature(i, feature););
	}

	*registro = nuevoRegistro;
	return cantidadLeida;
}

void HidratadorRegistro::Dispose()
{
	delete this;
}
