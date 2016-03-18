/* 
 * File:   iBitacora.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 21:19
 */

#ifndef IBITACORA_H
#define	IBITACORA_H

#include "../../../Exceptions/iException.h"

typedef class iBitacora
{
	public:
		virtual void Close() = 0;
	
		virtual void Log(const char *format) = 0;
		virtual void Log(iExceptionPtr exception) = 0;

} *iBitacoraPtr;

#endif	/* IBITACORA_H */
