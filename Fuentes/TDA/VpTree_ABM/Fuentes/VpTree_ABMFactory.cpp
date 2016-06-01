/*
 * VpTree_ABMFactory.cpp
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#include "../Headers/VpTree_ABM.h"
#include "../VpTree_ABMFactory.h"

iVpTree_ABMPtr VpTree_ABMFactory_Nuevo(const char* _fileName,
		size_t _tamanioNodo, size_t _cargaMinima,
		size_t _tolerancia) {

	return new VpTree_ABM(_fileName, _tamanioNodo, _cargaMinima,
			_tolerancia);
}
