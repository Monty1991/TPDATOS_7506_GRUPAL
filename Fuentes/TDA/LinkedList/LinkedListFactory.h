/* 
 * File:   LinkedListFactory.h
 * Author: Monty
 *
 * Created on 20 de marzo de 2016, 21:52
 */

#ifndef LINKEDLISTFACTORY_H
#define	LINKEDLISTFACTORY_H

#include "Headers/iLinkedList.h"

iLinkedListPtr LinkedListFactory_Nuevo(iObjectPtr obj, iLinkedListPtr next);

#endif	/* LINKEDLISTFACTORY_H */

