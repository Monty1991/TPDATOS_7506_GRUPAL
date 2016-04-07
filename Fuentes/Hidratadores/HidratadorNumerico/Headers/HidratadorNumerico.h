/* 
 * File:   HidratadorNumerico.h
 * Author: Monty
 *
 * Created on 4 de abril de 2016, 23:58
 */

#ifndef HIDRATADORNUMERICO_H
#define	HIDRATADORNUMERICO_H

#include "iHidratadorNumerico.h"

class HidratadorNumerico: public iHidratadorNumerico
{
	private:

	public:
		HidratadorNumerico();
		virtual ~HidratadorNumerico();

		size_t Hidratar(const char *buff, uNumber *numero, eValueType tipo);
		
		virtual void Dispose();

	private:
		size_t CalcularEspacio(const char *buff, eValueType tipo);

};

#endif	/* HIDRATADORNUMERICO_H */

