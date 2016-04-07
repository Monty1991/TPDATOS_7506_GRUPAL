/*
 * SerializadorTTDispersion.cpp
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#include <cstring>
#include "../Headers/SerializadorTTDispersion.h"
#include "../../../Utils/CaracterUtils/Headers/CaracterUtils.h"

unsigned SerializadorTTDispersion::calcularEspacio(
		const iTTDispersionPtr _tabla) {
	return _tabla->getTamanio() * 2 + 2;
}

unsigned SerializadorTTDispersion::serializar(const iTTDispersionPtr _tabla,
		char* _buffer) {

	unsigned usefulChars;
	int nroBloque;
	char* usefulCharsPtr = (char*) &usefulChars;
	char* nroBloquePtr = (char*) &nroBloque;

	if (big_endian()) {

		usefulCharsPtr += ((sizeof(unsigned)) - 2);
		nroBloquePtr += ((sizeof(int)) - 2);
	}

	usefulChars = calcularEspacio(_tabla);
	memcpy(_buffer, usefulCharsPtr, 2);
	_buffer += 2;

	for (unsigned i = 0; i < _tabla->getTamanio(); i++) {

		nroBloque = _tabla->getElement(i);
		memcpy(_buffer, nroBloquePtr, 2);
		_buffer += 2;
	}

	return usefulChars;
}

