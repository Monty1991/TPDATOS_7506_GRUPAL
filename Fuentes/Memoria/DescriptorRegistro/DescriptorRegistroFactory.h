/* 
 * File:   DescriptorRegistroFactory.h
 * Author: Monty
 *
 * Created on 11 de junio de 2016, 14:33
 */

#ifndef DESCRIPTORREGISTROFACTORY_H
#define DESCRIPTORREGISTROFACTORY_H

#include "Headers/iDescriptorRegistro.h"

iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(const sDescriptorCampoPtr tablaDescriptorCampo, size_t cantidadDescriptoresCampo);

//	La cadena es de formato 'MX[,...]' donde:
//	M es (U: Unsigned, I: signed, F: flotante, C: cadena tamanio fijo, V: cadena variable)
//	X es un modificador numerico, cantidad de bits, para numeros, 32 o 64 para flotantes, la longitud para cadenas.
//		Si es cero, se admiten cadenas de cualquier longitud
iDescriptorRegistroPtr DescriptorRegistroFactory_Nuevo(const char *cadenaDescriptorRegistro);

#endif /* DESCRIPTORREGISTROFACTORY_H */
