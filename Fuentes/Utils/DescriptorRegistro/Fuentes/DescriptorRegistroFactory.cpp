#include "../DescriptorRegistroFactory.h"
#include "../Headers/DescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(eValueType *valores, int cantidad)
{
	return new DescriptorRegistro(valores, cantidad);
}
