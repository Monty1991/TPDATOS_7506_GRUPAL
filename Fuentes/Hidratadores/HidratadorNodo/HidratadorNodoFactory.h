/* 
 * File:   HidratadorNodoFactory.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 23:54
 */

#ifndef HIDRATADORNODOFACTORY_H
#define HIDRATADORNODOFACTORY_H

#include "Headers/iHidratadorNodo.h"

iHidratadorNodoPtr HidratadorNodoFactory_Nuevo(eHidratadorNodo tipoNodo);

#endif /* HIDRATADORNODOFACTORY_H */
