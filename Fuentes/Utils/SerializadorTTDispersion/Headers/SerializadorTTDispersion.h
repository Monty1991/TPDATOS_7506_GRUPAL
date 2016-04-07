/*
 * SerializadorTTDispersion.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef SERIALIZADORTTDISPERSION_H_
#define SERIALIZADORTTDISPERSION_H_

#include "iSerializadorTTDispersion.h"

class SerializadorTTDispersion: public iSerializadorTTDispersion {

public:

	virtual ~SerializadorTTDispersion() {

	}

	unsigned calcularEspacio(const iTTDispersionPtr _tabla);

	unsigned serializar(const iTTDispersionPtr _tabla, char* _buffer);

};

#endif /* SERIALIZADORTTDISPERSION_H_ */
