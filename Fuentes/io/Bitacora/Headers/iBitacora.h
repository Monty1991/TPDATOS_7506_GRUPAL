/* 
 * File:   iLogger.h
 * Author: Monty
 *
 * Created on 15 de marzo de 2016, 23:49
 */

#ifndef ILOGGER_H
#define	ILOGGER_H

typedef class iBitacora
{
	public:

		virtual void Close() = 0;

		virtual void Log(const char *string) = 0;
} *iBitacoraPtr;

#endif	/* ILOGGER_H */
