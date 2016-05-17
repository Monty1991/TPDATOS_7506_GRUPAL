#include "../HidratadorNodoFactory.h"
#include "../Headers/HidratadorNodo.h"

iHidratadorNodoPtr HidratadorNodoFactory_Nuevo(eHidratadorNodo tipoNodo)
{
	switch(tipoNodo)
	{
		case eHidratadorNodo_ArbolPuntoOptimo:
			return new HidratadorNodo();
	}

	// TODO: lanzar excepcion?
	
	return NULL;
}
