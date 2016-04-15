/*
 * SerializadorTTDispersionFactory.cpp
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#include "../SerializadorTTDispersionFactory.h"
#include "../Headers/SerializadorTTDispersion.h"

iSerializadorTTDispersionPtr SerializadorTTDispersionFactory_Nuevo() {
	return new SerializadorTTDispersion();
}

