#include "../NodoArbolPuntoOptimoFactory.h"
#include "../Headers/NodoArbolPuntoOptimo.h"

iNodoArbolPuntoOptimoNodoHojaPtr NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo tipoNodo)
{
	switch (tipoNodo)
	{
		case eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja:
			return new NodoArbolPuntoOptimoNodoHoja(NULL, 0);

		case eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno:
			return new NodoArbolPuntoOptimoNodoInterno(NULL, 0);
	}

	return NULL;
}

iNodoArbolPuntoOptimoNodoHojaPtr NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo tipoNodo, iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	switch (tipoNodo)
	{
		case eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja:
			return new NodoArbolPuntoOptimoNodoHoja(listaRegistros, cantidadRegistros);

		case eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno:
			return new NodoArbolPuntoOptimoNodoInterno(listaRegistros, cantidadRegistros);
	}

	return NULL;
}
