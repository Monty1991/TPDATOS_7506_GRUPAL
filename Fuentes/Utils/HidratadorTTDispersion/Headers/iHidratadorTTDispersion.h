/*
 * iHidratadorTTDispersion.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef IHIDRATADORTTDISPERSION_H_
#define IHIDRATADORTTDISPERSION_H_

#include "../../TTDispersion/Headers/iTTDispersion.h"

typedef class iHidratadorTTDispersion {

public:

	virtual ~iHidratadorTTDispersion() {

	}

	virtual unsigned hidratar(iTTDispersionPtr _tabla, const char* _buffer)=0;

}*iHidratadorTTDispersionPtr;

#endif /* IHIDRATADORTTDISPERSION_H_ */
