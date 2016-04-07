/*
 * SerializadorByteMapFactory.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef SERIALIZADORBYTEMAPFACTORY_H_
#define SERIALIZADORBYTEMAPFACTORY_H_

#include "./Headers/iSerializadorByteMap.h"

class SerializadorByteMapFactory {

public:

	iSerializadorByteMapPtr SerializadorByteMapFactory_Nuevo();
};

#endif /* SERIALIZADORBYTEMAPFACTORY_H_ */
