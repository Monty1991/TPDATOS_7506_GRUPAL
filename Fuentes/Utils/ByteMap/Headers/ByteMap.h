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

using namespace std;

class ByteMap: public iByteMap {

private:

	struct Gap {
		unsigned long ref;
		unsigned cantBytes;
	};

	eConfiguracion config;
	vector<Gap> listGaps;

	void insert(unsigned _pos, const Gap& _g);
	bool existe(unsigned long _ref, unsigned& _pos) const;
	int insertOrdenado(const Gap& _g);

public:

	ByteMap(eConfiguracion _config) :
			config(_config) {
		listGaps.clear();
	}

	ByteMap(const ByteMap& _byteMap);

	virtual ~ByteMap() {
	}

	iByteMap* clone() const {
		return new ByteMap(*this);
	}

	eConfiguracion getConfiguracion() const {
		return config;
	}

	unsigned getTamanio() const {
		return listGaps.size();
	}

	void reduce();

	void enlarge(unsigned long _referencia, unsigned _cantBytesLibres);

	void upDate(unsigned long _referencia, int _cantBytesModificados);

	unsigned getCantBytesLibres(unsigned long _referencia);

	long getReferencia(unsigned _cantBytesNecesarios) const;

};

#endif /* BYTEMAP_H_ */
