/*
 * SerializadorTTDispersionFactory.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef SERIALIZADORTTDISPERSIONFACTORY_H_
#define SERIALIZADORTTDISPERSIONFACTORY_H_

#include "Headers/iSerializadorTTDispersion.h"

class SerializadorTTDispersionFactory {

public:

	iSerializadorTTDispersionPtr SerializadorTTDispersionFactory_Nuevo();
};

#endif /* SERIALIZADORTTDISPERSIONFACTORY_H_ */
