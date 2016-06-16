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
#include "../../../Utils/EspacioMetrico/Headers/iEspacioMetrico.h"

enum eHermanoVpTree_ABM {
	eHermanoVpTree_ABM__Hoja,
	eHermanoVpTree_ABM__NodoInterno,
	eHermanoVpTree_ABM__Inexistente
};

class VpTree_ABM: public iVpTree_ABM {

private:

	size_t nroCampoClave;
	iArchivoArbolPtr archivo;
	iNodoArbolPuntoOptimoPtr raiz;
	iEspacioMetricoPtr espacioMetrico;

	virtual ~VpTree_ABM();

	//Resuelve el underflow de un nodo interno
	//Todos los nodos actualizados son escritos a disco
	//Luego de la invocación los nodos pasados como parámetro contienen basura
	void ResolverUnderflow(size_t _nroNodoPadre,
			iNodoArbolPuntoOptimoNodoInternoPtr _padre);

	//Resuelve el underflow de un nodo hoja
	//Todos los nodos actualizados son escritos a disco
	//Luego de la invocación los nodos pasados como parámetro contienen basura
	void ResolverUnderflow(size_t _nroNodoPadre,
			iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
			iNodoArbolPuntoOptimoNodoHojaPtr _hijo);

	//Resuelve el overflow de un nodo hoja
	//Todos los nodos actualizados son escritos a disco
	//Luego de la invocación los nodos pasados como parámetro contienen basura
	void ResolverOverflow(size_t _nroNodoHijo,
			iNodoArbolPuntoOptimoNodoHojaPtr _hijo);

	//Genera un nuevo pivote a partir del conjunto de registros en la hoja
	iFeaturePtr GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	//PRE: llamar a GenerarPivote(_hoja)
	double CalcularRadio(iFeaturePtr _pivote,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	double Distancia(iFeaturePtr _key1, iFeaturePtr _key2);

	//Obtiene el hermano del hijo pasado como parámetro
	eHermanoVpTree_ABM ObtenerHermano(
			iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
			size_t* _nroNodoHermano, iNodoArbolPuntoOptimoPtr* _hermano);

	//Devuelve el nodo fusión entre padre e hijo
	//Luego de la invocación los nodos pasados como parámetro contienen basura
	iNodoArbolPuntoOptimoPtr Fusionar(
			iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
			iNodoArbolPuntoOptimoNodoHojaPtr _hijo);

	// Reparte los contenidos de un nodo entre 2 y devuelve el radio
	double Repartir(iNodoArbolPuntoOptimoPtr padre, iFeaturePtr pivote, iNodoArbolPuntoOptimoPtr hijo1, iNodoArbolPuntoOptimoPtr hijo2);
	
	//Busca la clave dentro del nodo
	//Si la encuentra devuelve su posición
	//Caso contrario devuelve NULL
	size_t Ubicar(iFeaturePtr clave, iNodoArbolPuntoOptimoPtr _nodo);

	//Escribe un nodo a disco
	//Usar este método garantiza que la raiz esté siempre bufferizada
	void Escribir(size_t _nroNodo, iNodoArbolPuntoOptimoPtr _nodo);

	//Procedimiento de alta recursivo
	//Luego de la invocación los nodos pasados como parámetro contienen basura
	eResultadoVpTree_ABM Alta(iRegistroPtr _reg, size_t _nroNodoPadre,
			iNodoArbolPuntoOptimoPtr _padre);

	//Procedimiento de baja recursivo
	//Luego de la invocación los nodos pasados como parámetro contienen basura
	eResultadoVpTree_ABM Baja(iFeaturePtr _key, size_t _nroNodoPadre,
			iNodoArbolPuntoOptimoPtr _padre, size_t _nroNodoHijo,
			iNodoArbolPuntoOptimoPtr _hijo);

public:

	VpTree_ABM(const char* _fileName, size_t _nroCampoClave,
			size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia);

	virtual eResultadoVpTree_ABM Alta(const iRegistroPtr _reg, bool _unicidad);

	virtual eResultadoVpTree_ABM Baja(const iFeaturePtr _key);

	virtual eResultadoVpTree_ABM Modificacion(const iRegistroPtr _reg);

	virtual eResultadoVpTree_ABM Buscar(const iFeaturePtr _key, iRegistroPtr *_reg);

	virtual void Dispose();

};

#endif /* VPTREE_ABM_H_ */
