/*
 * VpTree_ABM.h
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#ifndef VPTREE_ABM_H_
#define VPTREE_ABM_H_

#include "iVpTree_ABM.h"
#include "../../../io/ArchivoArbol/Headers/iArchivoArbol.h"
#include "../../../Utils/NodoArbolPuntoOptimo/Headers/iNodoArbolPuntoOptimo.h"

enum eHermanoVpTree_ABM
{
	eHermanoVpTree_ABM_Hoja,
	eHermanoVpTree_ABM_NodoInterno,
	eHermanoVpTree_ABM_Inexistente
};

class VpTree_ABM: public iVpTree_ABM
{
	private:
		size_t nroCampoClave;
		iArchivoArbolPtr archivo;
		iNodoArbolPuntoOptimoPtr raiz;

		virtual ~VpTree_ABM();

	public:
		VpTree_ABM(const char *archivo, size_t nroCampoClave, size_t tamanioNodo, size_t cargaMinima, size_t tolerancia);

		virtual eResultadoABM Alta(const iRegistroPtr registro, bool comprobarUnicidad);

		virtual eResultadoABM Baja(const iFeaturePtr clave);

		virtual eResultadoABM Modificacion(const iRegistroPtr registro);

		virtual eResultadoABM Buscar(const iFeaturePtr clave, iRegistroPtr *registro);

		virtual void Dispose();

	private:
		/****************************
			Persistencia a disco
		****************************/

		// Escribe un nodo a disco
		virtual void Escribir(size_t nroNodo, iNodoArbolPuntoOptimoPtr nodo);

		/******************************
			Metodos ABM recursivos
		******************************/
	
		// Procedimiento de alta recursivo
		virtual eResultadoABM Alta(iRegistroPtr registro, size_t nroNodo, iNodoArbolPuntoOptimoPtr nodo);

		// Procedimiento de baja recursivo
		virtual eResultadoABM Baja(iFeaturePtr clave, size_t nroNodo, iNodoArbolPuntoOptimoPtr nodo, size_t nroNodoHijo, iNodoArbolPuntoOptimoPtr nodoHijo);

		// Procedimiento de busqueda recursivo
		virtual eResultadoABM Buscar(const iFeaturePtr clave, iRegistroPtr *registro, iNodoArbolPuntoOptimoPtr nodo);

		/**************************
			De Espacio Metrico
		**************************/

		// Calcula la distancia entre 2 claves.
		// Pre: Ambas claves tienen que ser del mismo tipo, distintas de NULL
		virtual double Distancia(iFeaturePtr clave1, iFeaturePtr clave2);

		// Genera un nuevo pivote a partir del conjunto de registros en la hoja
		virtual iFeaturePtr GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr nodo);

		// Dado un pivote, calcula el radio que separa en 2 el contenido de una hoja
		virtual double CalcularRadio(iFeaturePtr pivote, iNodoArbolPuntoOptimoNodoHojaPtr nodo);

		// Dado un pivote, reparte los contenidos de un nodo entre otros 2 y devuelve el radio
		virtual double Partir(iNodoArbolPuntoOptimoPtr nodo, iFeaturePtr pivote, iNodoArbolPuntoOptimoPtr hijo1, iNodoArbolPuntoOptimoPtr hijo2);

		/**************************
			Auxiliares de nodo
		**************************/

		// Compara 2 claves, devuelve verdadero si son iguales.
		// Falso en caso contrario.
		virtual bool CompararClaves(iFeaturePtr clave1, iFeaturePtr clave2);

		// Busca un registro por clave dentro de un nodo
		// Si la encuentra devuelve su posición
		// Caso contrario devuelve nodo->ObtenerCantidadRegistros
		virtual size_t UbicarRegistro(iFeaturePtr clave, iNodoArbolPuntoOptimoPtr nodo);

		// Obtiene el hermano del hijo pasado como parámetro
		virtual eHermanoVpTree_ABM ObtenerHermano(iNodoArbolPuntoOptimoNodoInternoPtr nodoPadre, size_t nroNodoHijo, size_t *nroNodoHermano, iNodoArbolPuntoOptimoPtr *nodoHermano);

		// Por default a la izquierda
		virtual void AgregarHijo(iNodoArbolPuntoOptimoNodoInternoPtr nodoPadre, size_t nroNodoHijo);

		// Devuelve el nodo fusión entre padre e hijo
		virtual iNodoArbolPuntoOptimoPtr Fusionar(iNodoArbolPuntoOptimoNodoInternoPtr nodoPadre, size_t nroNodoHijo, iNodoArbolPuntoOptimoNodoHojaPtr nodoHijo);

		/********************************************
			Resolucion de overflows y underflows
		********************************************/

		// Resuelve el underflow de un nodo interno
		// Todos los nodos actualizados son escritos a disco
		// Luego de la invocación los nodos pasados como parámetro contienen basura
		virtual void ResolverUnderflow(size_t nroNodo, iNodoArbolPuntoOptimoNodoInternoPtr nodo);

		// Resuelve el underflow de un nodo hoja
		// Todos los nodos actualizados son escritos a disco
		// Luego de la invocación los nodos pasados como parámetro contienen basura
		virtual void ResolverUnderflow(size_t nroNodoPadre, iNodoArbolPuntoOptimoNodoInternoPtr padre, size_t nroNodoHijo, iNodoArbolPuntoOptimoNodoHojaPtr hijo);

		// Resuelve el overflow de un nodo hoja
		// Todos los nodos actualizados son escritos a disco
		virtual void ResolverOverflow(size_t nroNodo, iNodoArbolPuntoOptimoNodoHojaPtr nodo);
};

#endif /* VPTREE_ABM_H_ */
