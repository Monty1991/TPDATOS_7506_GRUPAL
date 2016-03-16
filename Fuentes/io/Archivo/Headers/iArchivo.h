/* 
 * File:   iArchivo.h
 * Author: Monty
 *
 * Created on 16 de marzo de 2016, 12:21
 */

#ifndef IARCHIVO_H
#define	IARCHIVO_H

typedef class iArchivo
{
	public:

		// Acceso aleatorio
		virtual void Read(char *buff, int amount) = 0;
		virtual void Write(char *buff, int amount) = 0;
		virtual void Seek(int position) = 0;

		// Acceso secuencial
		virtual int ReadChar() = 0;
		virtual void WriteChar(int c) = 0;
		virtual void Printf(const char *format, ...) = 0;

		virtual void Flush() = 0;
		virtual void Close() = 0;
	
} *iArchivoPtr;

#endif	/* IARCHIVO_H */
