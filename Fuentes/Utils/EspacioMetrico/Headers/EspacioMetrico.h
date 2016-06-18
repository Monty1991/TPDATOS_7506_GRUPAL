/* 
 * File:   EspacioMetrico.h
 * Author: Monty
 *
 * Created on 1 de junio de 2016, 00:52
 */

#ifndef ESPACIOMETRICO_H
#define ESPACIOMETRICO_H

#include "../../../Memoria/DataType.h"

double EspacioMetrico_CalcularDistancia(size_t clave2, size_t clave1);
double EspacioMetrico_CalcularDistancia(sCadenaANSI *clave1, sCadenaANSI *clave2);

size_t EspacioMetrico_CalcularPivote(size_t *listaClaves, size_t cantidadClaves);
sCadenaANSI *EspacioMetrico_CalcularPivote(sCadenaANSI **listaClaves, size_t cantidadClaves);

#endif /* ESPACIOMETRICO_H */
