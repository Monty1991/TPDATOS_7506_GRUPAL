/*
 * FechaFactory.h
 *
 *  Created on: 27/03/2016
 *      Author: cristian
 */

#ifndef FECHAFACTORY_H_
#define FECHAFACTORY_H_

#include "Headers/iFecha.h"
#include "Headers/Fecha.h"

iFechaPtr FechaFactory_Nuevo(unsigned char _dia, unsigned char _mes,
		unsigned int _anio, unsigned char _hora, unsigned char _minuto,
		unsigned char _segundo);

#endif /* FECHAFACTORY_H_ */
