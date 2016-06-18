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

size_t RegistroFactory_CalcularEspacioSerializacion(const iRegistroPtr registro);
size_t RegistroFactory_Serializar(char *buffer, const iRegistroPtr registro);
size_t RegistroFactory_Hidratar(const char *buff, iRegistroPtr *registro);

#endif /* REGISTROFACTORY_H */
