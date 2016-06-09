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
	float CalcularRadio(iFeaturePtr _pivote,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	float Distancia(iFeaturePtr _key1, iFeaturePtr _key2);

	//Obtiene el hermano del hijo pasado como parámetro
	eHermanoVpTree_ABM ObtenerHermano(
			iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
			size_t* _nroNodoHermano, iNodoArbolPuntoOptimoPtr* _hermano);

	//Devuelve el nodo fusión entre padre e hijo
	//Luego de la invocación los nodos pasados como parámetro contienen basura
	iNodoArbolPuntoOptimoPtr Fusionar(
			iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
			iNodoArbolPuntoOptimoNodoHojaPtr _hijo);

	//Garantiza que la raiz esté siempre bufferizada
	void Escribir(size_t _nroNodo, iNodoArbolPuntoOptimoPtr _nodo);

public:

	VpTree_ABM(const char* _fileName, size_t _nroCampoClave,
			size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia);

	eResultadoVpTree_ABM Alta(iRegistroPtr _reg);

	eResultadoVpTree_ABM Baja(iFeaturePtr _key);

	eResultadoVpTree_ABM Modificacion(iRegistroPtr _reg);

	eResultadoVpTree_ABM Buscar(iRegistroPtr _reg);

	virtual void Dispose();

};

#endif /* VPTREE_ABM_H_ */
