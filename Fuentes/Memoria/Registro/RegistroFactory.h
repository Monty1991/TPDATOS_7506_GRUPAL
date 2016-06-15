/* 
 * File:   RegistroFactory.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 05:08
 */

#ifndef REGISTROFACTORY_H
#define REGISTROFACTORY_H

#include "Headers/iRegistro.h"
#include "../DescriptorRegistro/Headers/iDescriptorRegistro.h"

iRegistroPtr RegistroFactory_Nuevo(size_t cantidadCampos);
iRegistroPtr RegistroFactory_Nuevo(iDescriptorRegistroPtr descriptor, const char *cadena);

#endif /* REGISTROFACTORY_H */
