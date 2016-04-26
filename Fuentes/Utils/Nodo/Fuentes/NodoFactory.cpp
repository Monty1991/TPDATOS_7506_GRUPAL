#include "../NodoFactory.h"
#include "../Headers/Nodo.h"
#include <stdlib.h>

iNodoPtr NodoFactory_Nuevo(size_t altura, iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	return new Nodo(altura, listaRegistros, cantidadRegistros);
}
