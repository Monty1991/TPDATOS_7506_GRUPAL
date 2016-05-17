
/* 
 * File:   iSerializadorNodo.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 12:53
 */

#ifndef ISERIALIZADORNODO_H
#define ISERIALIZADORNODO_H

#include "../../../Utils/Nodo/Headers/iNodo.h"

enum eSerializadorNodo
{
	eSerializadorNodo_ArbolPuntoOptimo
};

typedef class iSerializadorNodo
{
	public:
		virtual size_t CalcularEspacioSerializacion(iNodoPtr nodo) = 0;

		virtual size_t Serializar(char *buff, iNodoPtr nodo) = 0;
		
		virtual void Dispose() = 0;
} *iSerializadorNodoPtr;

#endif /* ISERIALIZADORNODO_H */
