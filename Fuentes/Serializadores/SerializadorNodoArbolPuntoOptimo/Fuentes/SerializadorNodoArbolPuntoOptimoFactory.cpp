#include "../SerializadorNodoArbolPuntoOptimoFactory.h"
#include "../Headers/SerializadorNodoArbolPuntoOptimo.h"

iSerializadorNodoPtr SerializadorNodoArbolPuntoOptimoFactory_Nuevo()
{
	return new SerializadorNodoArbolPuntoOptimo();
}
