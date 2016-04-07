/*
 * TTDispersion.cpp
 *
 *  Created on: 19/10/2014
 *      Author: cristian
 */

#include "../Headers/TTDispersion.h"
#include "../../../Exceptions/ExceptionFactory.h"

TTDispersion::TTDispersion(unsigned _tamanio) {

	res_fn_disp = 0;
	elementos.clear();

	for (unsigned i = 0; i < _tamanio; i++)
		elementos.push_back(-1);
}

iTTDispersion& TTDispersion::operator =(const iTTDispersion& _tabla) {

	res_fn_disp = ((TTDispersion&) _tabla).res_fn_disp;
	elementos.clear();

	for (unsigned i = 0; i < _tabla.getTamanio(); i++)
		elementos.push_back(((TTDispersion&) _tabla).elementos[i]);

	return *this;
}

void TTDispersion::duplicar() {

	unsigned tamAntes = elementos.size();

	for (unsigned i = 0; i < tamAntes; i++)
		elementos.push_back(elementos[i]);
}

bool TTDispersion::duplicada() const {

	unsigned tamanio = elementos.size();

	if ((tamanio % 2) != 0)
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

	if ((tamAntes % 2) != 0)
		Throw(" ", "TablaDeTamanioImpar");

	for (unsigned i = 0; i < (tamAntes / 2); i++)
		elementos.pop_back();
}

void TTDispersion::setElement(unsigned _pos, int _elem) {

	if (_pos >= elementos.size())
		Throw(" ", "PosicionInvalida");

	elementos[_pos] = _elem;
}

int TTDispersion::getElement(unsigned _pos) const {

	if (_pos >= elementos.size())
		Throw(" ", "PosicionInvalida");

	return elementos[_pos];
}

