#include "../SerializadorCadenaSinPrefijoFactory.h"
#include "../Headers/SerializadorCadenaSinPrefijo.h"

iSerializadorCadenaSinPrefijoPtr SerializadorCadenaSinPrefijoFactory_Nuevo()
{
	return new SerializadorCadenaSinPrefijo();
}
