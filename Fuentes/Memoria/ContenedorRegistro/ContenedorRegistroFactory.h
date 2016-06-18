/* 
 * File:   ContenedorRegistroFactory.h
 * Author: Monty
 *
 * Created on 18 de junio de 2016, 18:28
 */

#ifndef CONTENEDORREGISTROFACTORY_H
#define CONTENEDORREGISTROFACTORY_H

#include "Headers/iContenedorRegistro.h"

iContenedorRegistroPtr ContenedorRegistroFactory_Nuevo(iRegistroPtr *listaRegistros, size_t cantidadRegistros);

#endif /* CONTENEDORREGISTROFACTORY_H */
