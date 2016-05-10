#include "../DescriptorRegistroFactory.h"
#include "../Headers/DescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(eValueType *valores, size_t cantidad)
{
	return new DescriptorRegistro(valores, cantidad);
}
