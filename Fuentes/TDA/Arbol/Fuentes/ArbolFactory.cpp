#include "../ArbolFactory.h"
#include "../Headers/Arbol.h"

iArbolPtr ArbolFactory_Nuevo(int key, iObjectPtr valor)
{
	return new Arbol(key, valor);
}
