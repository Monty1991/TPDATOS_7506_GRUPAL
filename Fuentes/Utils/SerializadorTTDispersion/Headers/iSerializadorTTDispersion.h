/*
 * iSerializadorTTDispersion.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef ISERIALIZADORTTDISPERSION_H_
#define ISERIALIZADORTTDISPERSION_H_

#include "../../TTDispersion/Headers/iTTDispersion.h"

typedef class iSerializadorTTDispersion {

public:

	virtual ~iSerializadorTTDispersion() {

	}

	virtual unsigned calcularEspacio(const iTTDispersionPtr _tabla)=0;

	virtual unsigned serializar(const iTTDispersionPtr _tabla, char* _buffer)=0;

}*iSerializadorTTDispersionPtr;

#endif /* ISERIALIZADORTTDISPERSION_H_ */
