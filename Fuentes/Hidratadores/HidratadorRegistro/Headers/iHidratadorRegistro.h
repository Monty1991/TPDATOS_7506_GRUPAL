/* 
 * File:   iHidratadorRegistro.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 04:32
 */

#ifndef IHIDRATADORREGISTRO_H
#define IHIDRATADORREGISTRO_H

#include "../../../Memoria/Registro/Headers/iRegistro.h"
#include "../../../Utils/DescriptorRegistro/Headers/iDescriptorRegistro.h"

typedef class iHidratadorRegistro
{
	public:
		virtual size_t Hidratar(char *buff, iRegistroPtr *registro, iDescriptorRegistroPtr descriptorRegistro) = 0;
		
		virtual void Dispose() = 0;
} *iHidratadorRegistroPtr;

#endif /* IHIDRATADORREGISTRO_H */
