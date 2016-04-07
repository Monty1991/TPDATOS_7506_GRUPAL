/*
 * iHidratadorByteMap.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef IHIDRATADORBYTEMAP_H_
#define IHIDRATADORBYTEMAP_H_

#include "../../ByteMap/Headers/iByteMap.h"

typedef class iHidratadorByteMap {

public:

	virtual ~iHidratadorByteMap() {

	}

	virtual unsigned hidratar(iByteMapPtr _mapa, const char* _buffer) = 0;

}*iHidratadorByteMapPtr;

#endif /* IHIDRATADORBYTEMAP_H_ */
