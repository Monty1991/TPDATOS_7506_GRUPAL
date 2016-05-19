#include "../HidratadorNodoFactory.h"
#include "../Headers/HidratadorNodo.h"

iHidratadorNodoPtr HidratadorNodoFactory_Nuevo(eTipoArbol tipoArbol)
{
	switch(tipoArbol)
	{
		case eTipoArbol_ArbolPuntoOptimo:
			return new HidratadorNodo();
	}

	// TODO: lanzar excepcion?
	
	return NULL;
}
