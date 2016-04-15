/*
 * HidratadorByteMapFactory.cpp
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#include "../HidratadorByteMapFactory.h"
#include "../Headers/HidratadorByteMap.h"

iHidratadorByteMapPtr HidratadorByteMapFactory_Nuevo() {
	return new HidratadorByteMap();
}

