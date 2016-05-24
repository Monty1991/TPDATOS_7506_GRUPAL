#include "../HidratadorNodoFactory.h"
#include "../../HidratadorNodoArbolPuntoOptimo/HidratadorNodoArbolPuntoOptimoFactory.h"

iHidratadorNodoPtr HidratadorNodoFactory_Nuevo(eTipoArbol tipoArbol)
{
	switch(tipoArbol)
	{
		case eTipoArbol_ArbolPuntoOptimo:
			return HidratadorNodoArbolPuntoOptimoFactory_Nuevo();
	}

	// TODO: lanzar excepcion?
	
	return NULL;
}
