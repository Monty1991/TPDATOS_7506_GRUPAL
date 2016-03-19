#include "../DescriptorRegistroFactory.h"
#include "../Headers/DescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(eTipoCampo *valores, size_t cantidad)
{
	return new DescriptorRegistro(valores, cantidad);
}
