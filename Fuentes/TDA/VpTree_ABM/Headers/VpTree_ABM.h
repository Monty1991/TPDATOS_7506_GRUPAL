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

enum eEstadoVpTree_ABM {
	eEstadoVpTree_ABM__HOJA_EN_OVERFLOW,
	eEstadoVpTree_ABM__HOJA_EN_UNDERFLOW,
	eEstadoVpTree_ABM__NODO_INTERNO_EN_UNDERFLOW
};

class VpTree_ABM: public iVpTree_ABM {

private:

	iNodoPtr raiz;
	iArchivoArbolPtr archivo;
	iDistanceFnPtr fnDistancia;

	virtual ~VpTree_ABM();

	/**
	 * Resuelve un estado del árbol y escribe los nodos actualizados en disco
	 *
	 * Aquel caso que no requiera de nodo interno, dicho parámetro es ignorado
	 * Aquel caso que no requiera de nodo hoja,    dicho parámetro es ignorado
	 */
	void ResolverEstado(eEstadoVpTree_ABM _estado,
			iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	void ResolverUnderflow(iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno);

	void ResolverUnderflow(iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	void ResolverOverflow(iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	/**Genera un nuevo pivote a partir del conjunto de registros en la _hoja**/
	iFeaturePtr GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

	//PRE: llamar a GenerarPivote(_hoja)
	float CalcularRadio(iFeaturePtr _pivote,
			iNodoArbolPuntoOptimoNodoHojaPtr _hoja);

public:

	VpTree_ABM(const char* _fileName, iDistanceFnPtr _fnDistancia,
			size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia);

	eResultadoVpTree_ABM Alta(iRegistroPtr _reg);

	eResultadoVpTree_ABM Baja(iFeaturePtr _key);

	eResultadoVpTree_ABM Modificacion(iRegistroPtr _reg);

	eResultadoVpTree_ABM Buscar(iRegistroPtr _reg);

	void Dispose();

};

#endif /* VPTREE_ABM_H_ */
