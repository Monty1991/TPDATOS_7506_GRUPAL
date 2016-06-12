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
	eResultadoVpTree_ABM__Ok,
	eResultadoVpTree_ABM__Duplicado,
	eResultadoVpTree_ABM__Inexistente,
};

typedef class iVpTree_ABM {

public:

	virtual eResultadoVpTree_ABM Alta(const  iRegistroPtr _reg, bool _unicidad)=0;

	virtual eResultadoVpTree_ABM Baja(const iFeaturePtr _key)=0;

	virtual eResultadoVpTree_ABM Modificacion(const iRegistroPtr _reg)=0;

	virtual eResultadoVpTree_ABM Buscar(const iFeaturePtr _key, iRegistroPtr *_reg) = 0;

	virtual void Dispose() = 0;

}*iVpTree_ABMPtr;

#endif /* IVPTREE_ABM_H_ */
