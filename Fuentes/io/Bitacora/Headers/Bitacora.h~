/* 
 * File:   Bitacora.h
 * Author: Monty
 *
 * Created on 16 de marzo de 2016, 13:21
 */

#ifndef BITACORA_H
#define	BITACORA_H

#include "../../Archivo/ArchivoFactory.h"
#include "iBitacora.h"

typedef class Bitacora: public iBitacora
{
	private:
		iArchivoPtr archivo;

	public:
		Bitacora();
		Bitacora(const char *nombre);
		~Bitacora();

		void Close();

		void Log(const char *format);
		void Log(iExceptionPtr exception);

	private:
		void LogTimeStamp();

} *BitacoraPtr;

#endif	/* BITACORA_H */
