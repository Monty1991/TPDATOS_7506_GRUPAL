#include "../ArbolFactory.h"
#include "../Headers/Arbol.h"

iArbolPtr ArbolFactory_Nuevo(iFeaturePtr clave, iObjectPtr valor)
{
	return new Arbol(clave, valor);
}
