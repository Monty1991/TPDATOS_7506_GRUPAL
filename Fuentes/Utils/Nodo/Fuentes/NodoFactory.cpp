#include "../NodoFactory.h"
#include "../Headers/Nodo.h"
#include <stdlib.h>

iNodoPtr NodoFactory_Nuevo(eTipoNodo tipo, iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	return new Nodo(tipo, listaRegistros, cantidadRegistros);
}
