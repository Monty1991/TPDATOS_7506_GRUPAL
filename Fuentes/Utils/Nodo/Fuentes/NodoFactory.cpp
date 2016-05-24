#include "../NodoFactory.h"
#include "../../NodoArbolPuntoOptimo/NodoArbolPuntoOptimoFactory.h"

iNodoPtr NodoFactory_Nuevo(eTipoArbol tipoArbol, size_t tipoNodo)
{
	switch (tipoArbol)
	{
		case eTipoArbol::eTipoArbol_ArbolPuntoOptimo:
			return NodoArbolPuntoOptimoFactory_Nuevo((eNodoArbolPuntoOptimo)tipoNodo);
	}

	return NULL;
}

iNodoPtr NodoFactory_Nuevo(eTipoArbol tipoArbol, size_t tipoNodo, iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	switch (tipoArbol)
	{
		case eTipoArbol_ArbolPuntoOptimo:
			return NodoArbolPuntoOptimoFactory_Nuevo((eNodoArbolPuntoOptimo)tipoNodo, listaRegistros, cantidadRegistros);
	}

	return NULL;
}
