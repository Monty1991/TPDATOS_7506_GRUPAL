/* 
 * File:   iHidratadorNodo.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 23:53
 */

#ifndef IHIDRATADORNODO_H
#define IHIDRATADORNODO_H

#include "../../../Utils/Nodo/Headers/iNodo.h"

typedef class iHidratadorNodo
{
	public:
		virtual size_t Hidratar(char *buff, iNodoPtr *nodo) = 0;
		
		virtual void Dispose() = 0;

} *iHidratadorNodoPtr;

#endif /* IHIDRATADORNODO_H */
