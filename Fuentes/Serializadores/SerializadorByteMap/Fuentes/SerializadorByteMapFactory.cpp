/*
 * SerializadorByteMapFactory.cpp
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#include "../SerializadorByteMapFactory.h"
#include "../Headers/SerializadorByteMap.h"

iSerializadorByteMapPtr SerializadorByteMapFactory::SerializadorByteMapFactory_Nuevo() {
	return new SerializadorByteMap();
}

