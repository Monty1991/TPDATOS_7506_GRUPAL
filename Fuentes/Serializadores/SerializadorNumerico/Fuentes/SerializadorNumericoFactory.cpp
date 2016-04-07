#include "../SerializadorNumericoFactory.h"
#include "../Headers/SerializadorNumerico.h"

iSerializadorNumericoPtr SerializadorNumericoFactory_Nuevo()
{
	return new SerializadorNumerico();
}
