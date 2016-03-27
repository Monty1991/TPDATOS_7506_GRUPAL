/*
 * ByteMap.h
 *
 *  Created on: 29/09/2014
 *      Author: cristian
 */

#ifndef BYTEMAP_H_
#define BYTEMAP_H_

#include <vector>
#include <string>
#include "iByteMap.h"
#include "../../../Exceptions/ExceptionFactory.h"

using namespace std;

class ByteMap: public iByteMap {

private:
	struct Gap {
		unsigned long ref; /**Representa un nro de block ó un offset según sea la config.**/
		unsigned cantBytes;/**Representa la cant de bytes libres en la locación.**/
	};

	eConfiguracion config;
	vector<Gap> listGaps;

	void insert(unsigned _pos, const Gap& _g);
	bool existe(unsigned long _ref, unsigned& _pos) const;
	int insertOrdenado(const Gap& _g) {
		unsigned pos;
		if (existe(_g.ref, pos))
			return -1;
		else {
			insert(pos, _g);
			return pos;
		}
	}

public:
	ByteMap(eConfiguracion _config) :
			config(_config) {
		listGaps.clear();
	}

	virtual ~ByteMap() {
	}

	eConfiguracion getConfiguracion() const {
		return config;
	}

	unsigned getTamanio() const {
		return listGaps.size();
	}

	void addGap(unsigned long _ref, unsigned _cantBytes);

	void upDateGap(unsigned long _ref, int _cantBytes);

	long getCantBytes(unsigned long ref);

	long getGap(unsigned _cantBytes) const;

};

#endif /* BYTEMAP_H_ */
