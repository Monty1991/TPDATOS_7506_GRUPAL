/*
 * HidratadorTTDispersionFactory.cpp
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#include "../HidratadorTTDispersionFactory.h"
#include "../Headers/HidratadorTTDispersion.h"

iHidratadorTTDispersionPtr HidratadorTTDispersionFactory_Nuevo() {
	return new HidratadorTTDispersion();
}
