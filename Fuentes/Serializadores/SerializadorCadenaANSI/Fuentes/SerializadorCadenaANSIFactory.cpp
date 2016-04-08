#include "../SerializadorCadenaANSIFactory.h"
#include "../Headers/SerializadorCadenaANSI.h"

iSerializadorCadenaANSIPtr SerializadorCadenaANSIFactory_Nuevo()
{
	return new SerializadorCadenaANSI();
}
