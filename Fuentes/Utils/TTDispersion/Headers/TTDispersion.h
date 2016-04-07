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

using namespace std;

class TTDispersion: public iTTDispersion {

private:

	vector<int> elementos;
	unsigned res_fn_disp;

	unsigned modulo(unsigned long _key) {
		return res_fn_disp = (_key % getTamanio());
	}

public:

	TTDispersion(unsigned _tamanio);

	virtual ~TTDispersion() {
	}

	iTTDispersion& operator=(const iTTDispersion& _tabla);

	unsigned getTamanio() const {
		return elementos.size();
	}

	unsigned getResFnDispersion() const {
		return res_fn_disp;
	}

	void duplicar();

	bool duplicada() const;

	void truncar();

	void setElement(unsigned _pos, int _elem);

	int getElement(unsigned _pos) const;

	int getElementFromKey(unsigned long _key) {
		return getElement(modulo(_key));
	}

};

#endif /* TTDISPERSION_H_ */
