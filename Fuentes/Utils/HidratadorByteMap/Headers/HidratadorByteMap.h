/*
 * HidratadorByteMap.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef HIDRATADORBYTEMAP_H_
#define HIDRATADORBYTEMAP_H_

#include "iHidratadorByteMap.h"

class HidratadorByteMap: public iHidratadorByteMap {

public:

	virtual ~HidratadorByteMap() {

	}

	unsigned hidratar(iByteMapPtr _mapa, const char* _buffer);

};

#endif /* HIDRATADORBYTEMAP_H_ */
