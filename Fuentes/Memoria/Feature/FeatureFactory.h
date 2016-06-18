/* 
 * File:   FeatureFactory.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 02:36
 */

#ifndef FEATUREFACTORY_H
#define FEATUREFACTORY_H

#include "Headers/iFeature.h"

#include "../DescriptorRegistro/Headers/iDescriptorRegistro.h"

iFeaturePtr FeatureFactory_Nuevo(uValue valor, eValueType tipo);
iFeaturePtr FeatureFactory_Nuevo(sCadenaANSI *cadena);
iFeaturePtr FeatureFactory_Nuevo(const sDescriptorCampoPtr descCampo, const char *cadena, char **cadenaSiguiente);

size_t FeatureFactory_CalcularEspacioSerializacion(const iFeaturePtr feature);
size_t FeatureFactory_Serializar(char *buffer, const iFeaturePtr feature);
size_t FeatureFactory_Hidratar(const char *buff, iFeaturePtr *feature);

#endif /* FEATUREFACTORY_H */
