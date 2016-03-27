#ifndef CARACTERUTILS_H_
#define CARACTERUTILS_H_

#include <cstring>

bool big_endian() {

	int entero = 1;
	char* p = (char*) &entero;
	return p[0] == 0x00;
}

bool isDigit(const char& _c);

unsigned char getDigit(const char& _c);

#endif
