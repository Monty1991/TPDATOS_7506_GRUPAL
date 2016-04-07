/*
 * HidratadorTTDispersion.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef HIDRATADORTTDISPERSION_H_
#define HIDRATADORTTDISPERSION_H_

#include "iHidratadorTTDispersion.h"

class HidratadorTTDispersion: public iHidratadorTTDispersion {

public:

	virtual ~HidratadorTTDispersion() {

	}

	unsigned hidratar(iTTDispersionPtr _tabla, const char* _buffer);

};

#endif /* HIDRATADORTTDISPERSION_H_ */
