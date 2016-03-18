/* 
 * File:   RegistroBaseFactory.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 12:49
 */

#ifndef REGISTROBASEFACTORY_H
#define	REGISTROBASEFACTORY_H

#include "Headers/iRegistroBase.h"

iRegistroBasePtr RegistroBaseFactory_Nuevo(size_t cantidadCampos);

#endif	/* REGISTROBASEFACTORY_H */
