/*
 * ByteMapFactory.cpp
 *
 *  Created on: 26/03/2016
 *      Author: cristian
 */

#include "../ByteMapFactory.h"

iByteMapPtr ByteMapFactory_Nuevo(eConfiguracion _config){
	return new ByteMap(_config);
}

