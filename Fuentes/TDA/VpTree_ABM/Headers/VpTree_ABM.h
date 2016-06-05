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

enum eEstadoVpTree_ABM {
	eEstadoVpTree_ABM__HojaEnOverflow,
	eEstadoVpTree_ABM__HojaEnUnderflow,
	eEstadoVpTree_ABM__NodoInternoEnUnderflow
};

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

	/**
	 * Resuelve un estado del árbol y escribe los nodos actualizados en disco
	 *
	 * Aquel caso que no requiera de nodo interno, dicho parámetro es ignorado
	 * Aquel caso que no requiera de nodo hoja,    dicho parámetro es ignorado
	 */
	void ResolverEstado(eEstadoVpTree_ABM _estado, size_t _nroNodoInterno,
			iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno, size_t _nroHoja,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	void ResolverUnderflow(size_t _nroNodoInterno,
			iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno);

	void ResolverUnderflow(size_t _nroNodoInterno,
			iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno, size_t _nroHoja,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	void ResolverOverflow(size_t _nroHoja,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	/**Genera un nuevo pivote a partir del conjunto de registros en la _hoja**/
	size_t GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	//PRE: llamar a GenerarPivote(_hoja)
	float CalcularRadio(iFeaturePtr _pivote,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	float Distancia(iFeaturePtr _key1, iFeaturePtr _key2);

	eHermanoVpTree_ABM ObtenerHermano(
			iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _hijo,
			iNodoArbolPuntoOptimoPtr* _hermano);

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
