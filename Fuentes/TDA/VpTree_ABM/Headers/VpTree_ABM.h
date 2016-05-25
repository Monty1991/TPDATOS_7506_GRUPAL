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
	eEstadoVpTree_ABM_UNDERFLOW_INTERNO,
	eEstadoVpTree_ABM_UNDERFLOW_HOJA,
	eEstadoVpTree_ABM_OVERFLOW_HOJA
};

class VpTree_ABM: public iVpTree_ABM {

private:

	iNodoPtr raiz;
	iArchivoArbolPtr archivo;
	iDistanceFnPtr fnDistancia;

	virtual ~VpTree_ABM();

	void ResolverEstado(eEstadoVpTree_ABM _estado,
			iNodoArbolPuntoOptimoNodoInternoPtr _pInterno,
			iNodoArbolPuntoOptimoNodoHojaPtr _pHoja);

	void ResolverUnderflow(iNodoArbolPuntoOptimoNodoInternoPtr _pInterno);

	void ResolverUnderflow(iNodoArbolPuntoOptimoNodoInternoPtr _pInterno,
			iNodoArbolPuntoOptimoNodoHojaPtr _pHoja);

	void ResolverOverflow(iNodoArbolPuntoOptimoNodoHojaPtr _pHoja);

	iFeaturePtr GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr _pHoja);

	float CalcularRadio(iFeaturePtr _pivote,
			iNodoArbolPuntoOptimoNodoHojaPtr _pHoja);

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
