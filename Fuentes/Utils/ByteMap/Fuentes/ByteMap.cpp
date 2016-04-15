/*
 * ByteMap.cpp
 *
 *  Created on: 29/09/2014
 *      Author: cristian
 */

#include "../Headers/ByteMap.h"
#include "../../../Exceptions/ExceptionFactory.h"

int ByteMap::insertOrdenado(const Gap& _g) {

	unsigned pos;

	if (existe(_g.ref, pos))
		return -1;
	else {

		insert(pos, _g);
		return pos;
	}
}

ByteMap::ByteMap(const ByteMap& _byteMap) {

	config = _byteMap.config;
	listGaps.clear();

	for (unsigned i = 0; i < _byteMap.listGaps.size(); i++)
		listGaps.push_back(_byteMap.listGaps[i]);
}

void ByteMap::insert(unsigned _pos, const Gap& _g) {

	if (_pos == listGaps.size())
		listGaps.push_back(_g);
	else {

		unsigned last = listGaps.size() - 1;
		listGaps.push_back(listGaps[last]);

		for (unsigned i = last; i > _pos; i--)
			listGaps[i] = listGaps[i - 1];

		listGaps[_pos] = _g;
	}
}

bool ByteMap::existe(unsigned long _ref, unsigned& _pos) const {

	unsigned i;
	bool encontrado = false;

	for (i = 0; i < listGaps.size(); i++)
		if (listGaps[i].ref > _ref)
			break;
		else if (listGaps[i].ref == _ref) {

			encontrado = true;
			break;
		}

	_pos = i;
	return encontrado;
}

void ByteMap::enlarge(unsigned long _referencia, unsigned _cantBytesLibres) {

	Gap g;
	int pos;
	g.ref = _referencia;
	g.cantBytes = _cantBytesLibres;

	if (((pos = insertOrdenado(g)) < 0))
		Throw(" ", "BytesLibresConReferenciasMultiples");

	if (config == eConfiguracion_file_rrlv) {

		if ((unsigned) pos != (listGaps.size() - 1)) {

			if (listGaps[pos + 1].ref < (_referencia + _cantBytesLibres)) {

				Throw(" ", "BytesLibresConReferenciasMultiples");

			} else if (listGaps[pos + 1].ref
					== (_referencia + _cantBytesLibres)) {

				listGaps[pos].cantBytes += listGaps[pos + 1].cantBytes;
				listGaps.erase(listGaps.begin() + pos + 1);
			}
		}

		if (pos != 0) {

			if ((listGaps[pos - 1].ref + listGaps[pos - 1].cantBytes)
					> _referencia) {

				Throw(" ", "BytesLibresConReferenciasMultiples");

			} else if ((listGaps[pos - 1].ref + listGaps[pos - 1].cantBytes)
					== _referencia) {

				listGaps[pos - 1].cantBytes += listGaps[pos].cantBytes;
				listGaps.erase(listGaps.begin() + pos);
			}
		}
	}
}

void ByteMap::upDate(unsigned long _referencia, int _cantBytesModificados) {

	unsigned pos;

	if (!existe(_referencia, pos))
		Throw(" ", "ReferenciaInexistente");

	if ((int) listGaps[pos].cantBytes < _cantBytesModificados)
		Throw(" ", "CantBytesMalEspecificada");

	listGaps[pos].cantBytes -= _cantBytesModificados;

	if (config == eConfiguracion_file_rrlv) {

		if (listGaps[pos].cantBytes == 0)
			listGaps.erase(listGaps.begin() + pos);
		else
			listGaps[pos].ref += _cantBytesModificados;
	}
}

void ByteMap::reduce() {

	if (listGaps.size() != 0)
		listGaps.pop_back();
}

unsigned ByteMap::getCantBytesLibres(unsigned long _referencia) {

	for (unsigned i = 0; i < listGaps.size(); i++)
		if (listGaps[i].ref == _referencia)
			return listGaps[i].cantBytes;

	Throw(" ", "ReferenciaInexistente");
}

long ByteMap::getReferencia(unsigned _cantBytesNecesarios) const {

	for (unsigned i = 0; i < listGaps.size(); i++)
		if (listGaps[i].cantBytes >= _cantBytesNecesarios)
			return listGaps[i].ref;

	return -1;
}

