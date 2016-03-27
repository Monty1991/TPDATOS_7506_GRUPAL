/*
 * TTDispersion.h
 *
 *  Created on: 19/10/2014
 *      Author: cristian
 */

#ifndef TTDISPERSION_H_
#define TTDISPERSION_H_

#include <string>
#include <vector>
#include "iTTDispersion.h"
#include "../../../Exceptions/ExceptionFactory.h"

using namespace std;

class TTDispersion: public iTTDispersion {

private:
	vector<unsigned> elementos;
	unsigned lastAccessedElemIndex;

public:
	TTDispersion(unsigned _elem);

	virtual ~TTDispersion() {
	}

	unsigned getTamanio() const {
		return elementos.size();
	}

	unsigned remember() const {
		return lastAccessedElemIndex;
	}

	void duplicar();

	bool duplicada() const;

	void truncar();

	void replaceElement(unsigned _pos, unsigned _elem);

	unsigned getElement(unsigned _pos);

	unsigned dispersar(unsigned long _key) {

		return getElement(_key % getTamanio());
	}

};

#endif /* TTDISPERSION_H_ */
