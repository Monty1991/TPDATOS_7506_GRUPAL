/* 
 * File:   HidratadorNodo.h
 * Author: Monty
 *
 * Created on 10 de mayo de 2016, 23:56
 */

#ifndef HIDRATADORNODO_H
#define HIDRATADORNODO_H

#include "iHidratadorNodo.h"
#include "../../HidratadorNumerico/HidratadorNumericoFactory.h"
#include "../../HidratadorRegistro/Headers/iHidratadorRegistro.h"

class HidratadorNodo: public iHidratadorNodo
{
	private:
		iHidratadorNumericoPtr hidratadorNumerico;
		iHidratadorRegistroPtr hidratadorRegistro;

		virtual ~HidratadorNodo();
	public:
		HidratadorNodo();

		virtual size_t Hidratar(char *buff, iNodoPtr *nodo);

		virtual void Dispose();
};

#endif /* HIDRATADORNODO_H */

