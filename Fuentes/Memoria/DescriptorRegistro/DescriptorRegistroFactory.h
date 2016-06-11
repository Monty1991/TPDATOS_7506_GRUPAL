/* 
 * File:   DescriptorRegistroFactory.h
 * Author: Monty
 *
 * Created on 11 de junio de 2016, 14:33
 */

#ifndef DESCRIPTORREGISTROFACTORY_H
#define DESCRIPTORREGISTROFACTORY_H

#include "Headers/iDescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(sDescriptorCampoPtr *tablaDescriptorCampo, size_t cantidadDescriptoresCampo);

#endif /* DESCRIPTORREGISTROFACTORY_H */
