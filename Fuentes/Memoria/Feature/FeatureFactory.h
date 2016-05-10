/* 
 * File:   FeatureFactory.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 02:36
 */

#ifndef FEATUREFACTORY_H
#define FEATUREFACTORY_H

#include "Headers/iFeature.h"

iFeaturePtr FeatureFactory_Nuevo(uValue valor, eValueType tipo);

#endif /* FEATUREFACTORY_H */

