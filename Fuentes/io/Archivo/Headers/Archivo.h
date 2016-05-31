/* 
 * File:   Archivo.h
 * Author: Monty
 *
 * Created on 15 de marzo de 2016, 22:16
 */

#ifndef ARCHIVO_H
#define	ARCHIVO_H

#include <stdio.h>
#include "iArchivo.h"

typedef class Archivo: public iArchivo
{
	private:
		FILE *file;

	public:
		Archivo(const char *nombre, const char *mode);
		virtual ~Archivo();

		virtual void Read(char *buff, size_t count);
		virtual void Write(const char *buff, size_t amount);
		virtual void Seek(size_t position);
		
		virtual fpos_t GetFileSize();

		virtual int ReadChar();
		virtual void WriteChar(int c);

		virtual void Printf(const char *format);

		virtual void Flush();
		virtual void Close();

} *ArchivoPtr;

#endif	/* ARCHIVO_H */
