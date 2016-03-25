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
		~Archivo();

		void Read(char *buff, size_t count);
		void Write(char *buff, size_t amount);
		void Seek(size_t position);

		int ReadChar();
		void WriteChar(int c);

		void Printf(const char *format);

		void Flush();
		void Close();

} *ArchivoPtr;

#endif	/* ARCHIVO_H */
