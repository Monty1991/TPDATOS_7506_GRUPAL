/*
 * HidratadorTTDispersion.cpp
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#include <cstring>
#include "../Headers/HidratadorTTDispersion.h"
#include "../../CaracterUtils/Headers/CaracterUtils.h"
#include "../../TTDispersion/TTDispersionFactory.h"

unsigned HidratadorTTDispersion::hidratar(iTTDispersionPtr _tabla,
		const char* _buffer) {

	unsigned usefulChars = 0;
	int nroBloque = 0;
	char* usefulCharsPtr = (char*) &usefulChars;
	char* nroBloquePtr = (char*) &nroBloque;

	if (big_endian()) {

		usefulCharsPtr += ((sizeof(unsigned)) - 2);
		nroBloquePtr += ((sizeof(int)) - 2);
	}

	memcpy(usefulCharsPtr, _buffer, 2);
	_buffer += 2;
	iTTDispersionPtr _tablaLocal = TTDispersionFactory_Nuevo(
			(usefulChars - 2) / 2);

	for (unsigned i = 0; i < _tablaLocal->getTamanio(); i++) {

		memcpy(nroBloquePtr, _buffer, 2);
		_buffer += 2;

		if ((int) nroBloquePtr[0] != -1 || (int) nroBloquePtr[1] != -1)
			_tablaLocal->setElement(i, nroBloque);
	}

	*_tabla = *_tablaLocal;
	delete _tablaLocal;
	return usefulChars;
}
