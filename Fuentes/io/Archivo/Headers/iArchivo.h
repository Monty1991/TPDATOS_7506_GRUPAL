/* 
 * File:   iArchivo.h
 * Author: Monty
 *
 * Created on 16 de marzo de 2016, 12:21
 */

#ifndef IARCHIVO_H
#define	IARCHIVO_H

#include <stdlib.h>
#include <stdio.h>

typedef class iArchivo
{
	public:

		// Acceso aleatorio
		virtual void Read(char *buff, size_t count) = 0;
		virtual void Write(const char *buff, size_t count) = 0;
		virtual void Seek(size_t position) = 0;

		// consulta tamanio archivo
		virtual fpos_t GetFileSize() = 0;

		// Acceso secuencial
		virtual int ReadChar() = 0;
		virtual void WriteChar(int c) = 0;

		virtual void Printf(const char *format) = 0;

		virtual void Flush() = 0;
		virtual void Close() = 0;
	
} *iArchivoPtr;

#endif	/* IARCHIVO_H */
