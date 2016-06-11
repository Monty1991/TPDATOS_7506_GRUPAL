#include "../DescriptorRegistroFactory.h"
#include "../Headers/DescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(sDescriptorCampoPtr *tablaDescriptorCampo, size_t cantidadDescriptoresCampo)
{
	return new DescriptorRegistro(tablaDescriptorCampo, cantidadDescriptoresCampo);
}
