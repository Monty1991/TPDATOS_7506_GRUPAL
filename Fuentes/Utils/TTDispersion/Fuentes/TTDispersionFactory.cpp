/*
 * TTDispersionFactory.cpp
 *
 *  Created on: 26/03/2016
 *      Author: cristian
 */

#include "../TTDispersionFactory.h"

iTTDispersionPtr TTDispersionFactory_Nuevo(unsigned _elem){
	return new TTDispersion(_elem);
}


