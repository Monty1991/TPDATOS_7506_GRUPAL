#include "../SerializadorNodoFactory.h"
#include "../Headers/SerializadorNodo.h"

iSerializadorNodoPtr SerializadorNodoFactory_Nuevo(eTipoArbol tipoArbol)
{
	switch (tipoArbol)
	{
		case eTipoArbol_ArbolPuntoOptimo:
			return new SerializadorNodo();	
	}

	// TODO: lanzar excepcion?
	return NULL;
}
