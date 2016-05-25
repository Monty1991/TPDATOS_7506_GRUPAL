/*
 * iVpTree_ABM.h
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#ifndef IVPTREE_ABM_H_
#define IVPTREE_ABM_H_

#include "../../../Memoria/Registro/Headers/iRegistro.h"

enum eResultadoVpTree_ABM {
	eResultadoVpTree_ABM_OK,
	eResultadoVpTree_ABM_DUPLICADO,
	eResultadoVpTree_ABM_INEXISTENTE,
};

typedef class iDistanceFn {

public:

	virtual float Evaluar(iFeaturePtr _key1, iFeaturePtr _key2)=0;

	virtual iDistanceFn* Clone()=0;

	virtual void Dispose()=0;

}* iDistanceFnPtr;

typedef class iVpTree_ABM {

public:

	virtual eResultadoVpTree_ABM Alta(iRegistroPtr _reg)=0;

	virtual eResultadoVpTree_ABM Baja(iFeaturePtr _key)=0;

	virtual eResultadoVpTree_ABM Modificacion(iRegistroPtr _reg)=0;

	virtual eResultadoVpTree_ABM Buscar(iRegistroPtr _reg) = 0;

	virtual void Dispose() = 0;

}*iVpTree_ABMPtr;

#endif /* IVPTREE_ABM_H_ */
