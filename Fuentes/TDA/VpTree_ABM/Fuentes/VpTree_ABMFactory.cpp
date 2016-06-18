/*
 * VpTree_ABMFactory.cpp
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#include "../Headers/VpTree_ABM.h"
#include "../VpTree_ABMFactory.h"

iVpTree_ABMPtr VpTree_ABMFactory_Nuevo(const char *fileName, size_t nroCampoClave, size_t tamanioNodo, size_t cargaMinima, size_t tolerancia)
{
	return new VpTree_ABM(fileName, nroCampoClave, tamanioNodo, cargaMinima, tolerancia);
}
