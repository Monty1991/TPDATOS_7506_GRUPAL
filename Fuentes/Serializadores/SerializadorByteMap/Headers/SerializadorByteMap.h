/*
 * SerializadorByteMap.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef SERIALIZADORBYTEMAP_H_
#define SERIALIZADORBYTEMAP_H_

#include "iSerializadorByteMap.h"

class SerializadorByteMap: public iSerializadorByteMap {

public:

	virtual ~SerializadorByteMap() {

	}

	unsigned calcularEspacio(const iByteMapPtr _mapa);

	unsigned serializar(const iByteMapPtr _mapa, char* _buffer);

};

#endif /* SERIALIZADORBYTEMAP_H_ */
