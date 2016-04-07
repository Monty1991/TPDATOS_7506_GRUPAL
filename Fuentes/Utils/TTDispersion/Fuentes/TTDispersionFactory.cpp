/*
 * TTDispersionFactory.cpp
 *
 *  Created on: 26/03/2016
 *      Author: cristian
 */

#include "../TTDispersionFactory.h"
#include "../Headers/TTDispersion.h"

iTTDispersionPtr TTDispersionFactory_Nuevo(unsigned _tamanio){
	return new TTDispersion(_tamanio);
}


