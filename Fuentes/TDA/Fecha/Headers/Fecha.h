/*
 * Fecha.h
 *
 *  Created on: 18/10/2015
 *      Author: cristian
 */

#ifndef FECHA_H_
#define FECHA_H_

#include <iostream>
#include "iFecha.h"

using namespace std;

class Fecha: public iFecha {

private:

	unsigned char dia;
	unsigned char mes;
	unsigned int anio;
	unsigned char hora;
	unsigned char minuto;
	unsigned char segundo;

public:

	Fecha(unsigned char _dia, unsigned char _mes, unsigned int _anio,
			unsigned char _hora, unsigned char _minuto, unsigned char _segundo) :
			dia(_dia), mes(_mes), anio(_anio), hora(_hora), minuto(_minuto), segundo(
					_segundo) {
	}

	virtual ~Fecha() {
	}

	bool isValid() const;

	bool operator<(const Fecha& _f) const;

	bool operator==(const Fecha& _f) const;

	int compare(const iFecha& _f) const;

	unsigned int getAnio() const {
		return anio;
	}

	void setAnio(unsigned int _anio) {
		anio = _anio;
	}

	unsigned char getDia() const {
		return dia;
	}

	void setDia(unsigned char _dia) {
		dia = _dia;
	}

	unsigned char getHora() const {
		return hora;
	}

	void setHora(unsigned char _hora) {
		hora = _hora;
	}

	unsigned char getMes() const {
		return mes;
	}

	void setMes(unsigned char _mes) {
		mes = _mes;
	}

	unsigned char getMinuto() const {
		return minuto;
	}

	void setMinuto(unsigned char _minuto) {
		minuto = _minuto;
	}

	unsigned char getSegundo() const {
		return segundo;
	}

	void setSegundo(unsigned char _segundo) {
		segundo = _segundo;
	}

};

#endif /* FECHA_H_ */
