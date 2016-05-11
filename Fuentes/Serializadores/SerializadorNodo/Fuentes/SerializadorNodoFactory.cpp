#include "../SerializadorNodoFactory.h"
#include "../Headers/SerializadorNodo.h"

iSerializadorNodoPtr SerializadorNodoFactory_Nuevo()
{
	return new SerializadorNodo();
}
