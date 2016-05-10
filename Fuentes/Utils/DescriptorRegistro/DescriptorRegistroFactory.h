/* 
 * File:   DescriptorRegistroFactory.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 03:46
 */

#ifndef DESCRIPTORREGISTROFACTORY_H
#define	DESCRIPTORREGISTROFACTORY_H

#include "Headers/iDescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(eValueType *valores, size_t cantidad);

#endif	/* DESCRIPTORREGISTROFACTORY_H */

