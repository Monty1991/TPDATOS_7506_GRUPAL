#include "../Headers/HidratadorRegistro.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Memoria/Registro/RegistroFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorRegistro::HidratadorRegistro()
{
}

HidratadorRegistro::~HidratadorRegistro()
{
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
		Sistema_Execute(cantidadLeida += FeatureFactory_Hidratar(buff + cantidadLeida, &feature););
		Sistema_Execute(nuevoRegistro->SetFeature(i, feature););
	}

	*registro = nuevoRegistro;
	return cantidadLeida;
}

void HidratadorRegistro::Dispose()
{
	delete this;
}
