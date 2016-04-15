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

public:

	TTDispersion(unsigned _tamanio);

	virtual ~TTDispersion() {
	}

	iTTDispersion& operator=(const iTTDispersion& _tabla);

	unsigned getTamanio() const {
		return elementos.size();
	}

	void duplicar();

	bool duplicada() const;

	void truncar();

	void setElement(unsigned _pos, int _elem);

	int getElement(unsigned _pos) const;

};

#endif /* TTDISPERSION_H_ */
