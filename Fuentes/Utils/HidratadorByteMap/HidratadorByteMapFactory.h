/*
 * HidratadorByteMapFactory.h
 *
 *  Created on: 06/04/2016
 *      Author: cristian
 */

#ifndef HIDRATADORBYTEMAPFACTORY_H_
#define HIDRATADORBYTEMAPFACTORY_H_

#include "Headers/iHidratadorByteMap.h"

class HidratadorByteMapFactory {

public:

	virtual ~HidratadorByteMapFactory() {

	}

	iHidratadorByteMapPtr HidratadorByteMapFactory_Nuevo();

};

#endif /* HIDRATADORBYTEMAPFACTORY_H_ */
