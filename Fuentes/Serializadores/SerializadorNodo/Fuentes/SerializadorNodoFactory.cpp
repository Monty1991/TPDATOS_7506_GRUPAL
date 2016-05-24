#include "../SerializadorNodoFactory.h"
#include "../../SerializadorNodoArbolPuntoOptimo/SerializadorNodoArbolPuntoOptimoFactory.h"

iSerializadorNodoPtr SerializadorNodoFactory_Nuevo(eTipoArbol tipoArbol)
{
	switch (tipoArbol)
	{
		case eTipoArbol::eTipoArbol_ArbolPuntoOptimo:
			return SerializadorNodoArbolPuntoOptimoFactory_Nuevo();	
	}

	// TODO: lanzar excepcion?
	return NULL;
}
