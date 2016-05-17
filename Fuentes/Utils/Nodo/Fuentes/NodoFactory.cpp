#include "../NodoFactory.h"
#include "../Headers/Nodo.h"
#include <stdlib.h>

iNodoPtr NodoFactory_Nuevo()
{
	return new Nodo(eTipoNodo_Hoja, NULL, 0);
}

iNodoPtr NodoFactory_Nuevo(eTipoNodo tipo, iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	return new Nodo(tipo, listaRegistros, cantidadRegistros);
}
