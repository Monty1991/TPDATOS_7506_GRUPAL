#include "../SerializadorNodoFactory.h"
#include "../Headers/SerializadorNodo.h"

iSerializadorNodoPtr SerializadorNodoFactory_Nuevo(eSerializadorNodo tipoNodo)
{
	switch (tipoNodo)
	{
		case eSerializadorNodo_ArbolPuntoOptimo:
			return new SerializadorNodo();	
	}

	// TODO: lanzar excepcion?
	return NULL;
}
