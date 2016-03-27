/*
 * ByteMap.cpp
 *
 *  Created on: 29/09/2014
 *      Author: cristian
 */

#include "../Headers/ByteMap.h"

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

void ByteMap::addGap(unsigned long _ref, unsigned _cantBytes) {

	Gap g;
	int pos;

	g.ref = _ref;
	g.cantBytes = _cantBytes;

	if (((pos = insertOrdenado(g)) < 0))
		Throw(" ", "BytesLibresConReferenciasMultiples");

	if (config == eConfiguracion_file_rrlv) {
		if ((unsigned) pos != (listGaps.size() - 1)) {
			if (listGaps[pos + 1].ref < (_ref + _cantBytes)) {
				Throw(" ", "BytesLibresConReferenciasMultiples");
			} else if (listGaps[pos + 1].ref == (_ref + _cantBytes)) {
				listGaps[pos].cantBytes += listGaps[pos + 1].cantBytes;
				listGaps.erase(listGaps.begin() + pos + 1);
			}
		}

		if (pos != 0) {
			if ((listGaps[pos - 1].ref + listGaps[pos - 1].cantBytes) > _ref) {
				Throw(" ", "BytesLibresConReferenciasMultiples");
			} else if ((listGaps[pos - 1].ref + listGaps[pos - 1].cantBytes)
					== _ref) {
				listGaps[pos - 1].cantBytes += listGaps[pos].cantBytes;
				listGaps.erase(listGaps.begin() + pos);
			}
		}
	}
}

void ByteMap::upDateGap(unsigned long _ref, int _cantBytes) {

	unsigned pos;

	if (!existe(_ref, pos))
		Throw(" ", "ReferenciaInexistente");

	if ((int) listGaps[pos].cantBytes < _cantBytes)
		Throw(" ", "CantBytesMalEspecificada");

	listGaps[pos].cantBytes -= _cantBytes;

	if (config == eConfiguracion_file_rrlv) {
		if (listGaps[pos].cantBytes == 0)
			listGaps.erase(listGaps.begin() + pos);
		else
			listGaps[pos].ref += _cantBytes;
	}
}

long ByteMap::getCantBytes(unsigned long ref) {

	for (unsigned i = 0; i < listGaps.size(); i++)
		if (listGaps[i].ref == ref)
			return listGaps[i].cantBytes;

	return -1;
}

long ByteMap::getGap(unsigned _cantBytes) const {

	for (unsigned i = 0; i < listGaps.size(); i++)
		if (listGaps[i].cantBytes >= _cantBytes)
			return listGaps[i].ref;

	return -1;
}

