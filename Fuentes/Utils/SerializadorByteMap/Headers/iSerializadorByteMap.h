/*
 * iSerializadorByteMap.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef ISERIALIZADORBYTEMAP_H_
#define ISERIALIZADORBYTEMAP_H_

#include "../../ByteMap/Headers/iByteMap.h"

typedef class iSerializadorByteMap {

public:

	virtual ~iSerializadorByteMap() {

	}

	virtual unsigned calcularEspacio(const iByteMapPtr _mapa)=0;

	virtual unsigned serializar(const iByteMapPtr _mapa, char* _buffer)=0;

}*iSerializadorByteMapPtr;

#endif /* ISERIALIZADORBYTEMAP_H_ */
