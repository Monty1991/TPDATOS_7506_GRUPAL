/*
 * HidratadorByteMap.cpp
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#include <cstring>
#include "../Headers/HidratadorByteMap.h"
#include "../../../Utils/CaracterUtils/Headers/CaracterUtils.h"

unsigned HidratadorByteMap::hidratar(iByteMapPtr _mapa, const char* _buffer) {

	unsigned copyUsefulChars;
	unsigned usefulChars = 0;
	unsigned cantBytes = 0;
	unsigned long offset = 0;
	char * cantBytesPtr = (char*) &cantBytes;
	char * offsetPtr = (char*) &offset;
	char * usefulCharsPtr = (char*) &usefulChars;

	if (big_endian()) {

		offsetPtr += (sizeof(unsigned long) - 4);
		cantBytesPtr += ((sizeof(unsigned)) - 2);
		usefulCharsPtr += ((sizeof(unsigned)) - 2);
	}

	memcpy(usefulCharsPtr, _buffer, 2);
	_buffer += 2;
	copyUsefulChars = usefulChars;
	usefulChars -= 2;

	if (_mapa->getConfiguracion() == eConfiguracion_file_blocks)

		while (usefulChars != 0) {

			memcpy(cantBytesPtr, _buffer, 2);
			_mapa->enlarge((usefulChars / 2) - 1, cantBytes);
			_buffer += 2;
			usefulChars -= 2;
		}

	else

		while (usefulChars != 0) {

			memcpy(cantBytesPtr, _buffer, 2);
			_buffer += 2;
			memcpy(offsetPtr, _buffer, 4);
			_buffer += 4;
			usefulChars -= 6;
			_mapa->enlarge(offset, cantBytes);
		}

	return copyUsefulChars;
}

