/*
 * TTDispersion.cpp
 *
 *  Created on: 19/10/2014
 *      Author: cristian
 */

#include "../Headers/TTDispersion.h"

TTDispersion::TTDispersion(unsigned _elem) {

	elementos.clear();
	elementos.push_back(_elem);
	lastAccessedElemIndex = 0;
}

void TTDispersion::duplicar() {

	unsigned tamAntes = elementos.size();

	for (unsigned i = 0; i < tamAntes; i++)
		elementos.push_back(elementos[i]);
}

bool TTDispersion::duplicada() const {

	unsigned tamanio = elementos.size();
	if (tamanio == 1)
		return false;

	unsigned i = 0;
	unsigned j = tamanio / 2;
	while (j < tamanio)
		if (elementos[i++] != elementos[j++])
			return false;

	return true;
}

void TTDispersion::truncar() {

	unsigned tamAntes = elementos.size();
	if (tamAntes == 1)
		Throw(" ", "ElementoUnico");

	for (unsigned i = 0; i < (tamAntes / 2); i++)
		elementos.pop_back();
}

void TTDispersion::replaceElement(unsigned _pos, unsigned _elem) {

	if (_pos >= elementos.size())
		Throw(" ", "PosicionInvalida");

	elementos[_pos] = _elem;
	lastAccessedElemIndex = _pos;
}

unsigned TTDispersion::getElement(unsigned _pos) {

	if (_pos >= elementos.size())
		Throw(" ", "PosicionInvalida");

	lastAccessedElemIndex = _pos;
	return elementos[_pos];
}

