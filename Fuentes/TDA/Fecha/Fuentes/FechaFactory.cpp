/*
 * FechaFactory.cpp
 *
 *  Created on: 27/03/2016
 *      Author: cristian
 */

#include "../FechaFactory.h"

iFechaPtr FechaFactory_Nuevo(unsigned char _dia, unsigned char _mes,
		unsigned int _anio, unsigned char _hora, unsigned char _minuto,
		unsigned char _segundo) {

	return new Fecha(_dia, _mes, _anio, _hora, _minuto, _segundo);

}

