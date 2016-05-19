/* 
 * File:   SerializadorNodoFactory.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 13:02
 */

#ifndef SERIALIZADORNODOFACTORY_H
#define SERIALIZADORNODOFACTORY_H

#include "Headers/iSerializadorNodo.h"

iSerializadorNodoPtr SerializadorNodoFactory_Nuevo(eTipoArbol tipoArbol);

#endif /* SERIALIZADORNODOFACTORY_H */
