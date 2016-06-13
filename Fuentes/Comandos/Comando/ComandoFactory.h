/* 
 * File:   ComandoFactory.h
 * Author: Monty
 *
 * Created on 12 de junio de 2016, 23:48
 */

#ifndef COMANDOFACTORY_H
#define COMANDOFACTORY_H

#include "Headers/iComando.h"

iComandoPtr ComandoFactory_Nuevo(const char *nombreComando);

#endif /* COMANDOFACTORY_H */
