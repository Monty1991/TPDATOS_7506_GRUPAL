#include "../SerializadorRegistroFactory.h"
#include "../Headers/SerializadorRegistro.h"

iSerializadorRegistroPtr SerializadorRegistroFactory_Nuevo()
{
	return new SerializadorRegistro();
}
