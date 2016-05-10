#include "../Headers/HidratadorRegistro.h"
#include "../../HidratadorFeature/HidratadorFeatureFactory.h"
#include "../../../Memoria/Registro/RegistroFactory.h"

HidratadorRegistro::HidratadorRegistro()
{
	this->hidratadorFeature = HidratadorFeatureFactory_Nuevo();
}

HidratadorRegistro::~HidratadorRegistro()
{
	if (this->hidratadorFeature)
		this->hidratadorFeature->Dispose();
}

size_t HidratadorRegistro::Hidratar(char *buff, iRegistroPtr *registro, iDescriptorRegistroPtr descriptorRegistro)
{
	size_t cantidadCampos = descriptorRegistro->ObtenerCantidadCampos();
	iRegistroPtr nuevoRegistro = RegistroFactory_Nuevo(cantidadCampos);
	size_t cantidadLeida = 0;

	iFeaturePtr feature;
	for (size_t i = 0; i < cantidadCampos; i++)
	{
		cantidadLeida += this->hidratadorFeature->Hidratar(buff +cantidadLeida, &feature, descriptorRegistro->ObtenerTipoCampo(i));
		nuevoRegistro->SetFeature(i, feature);
	}

	*registro = nuevoRegistro;
	return cantidadLeida;
}

void HidratadorRegistro::Dispose()
{
	delete this;
}
