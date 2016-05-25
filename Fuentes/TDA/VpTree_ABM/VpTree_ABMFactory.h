/*
 * VpTree_ABMFactory.h
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#ifndef VPTREE_ABMFACTORY_H_
#define VPTREE_ABMFACTORY_H_

#include "Headers/iVpTree_ABM.h"

iVpTree_ABMPtr VpTree_ABMFactory_Nuevo(const char* _fileName,
		iDistanceFnPtr _fnDistancia, size_t _tamanioNodo, size_t _cargaMinima,
		size_t _tolerancia);

#endif /* VPTREE_ABMFACTORY_H_ */
