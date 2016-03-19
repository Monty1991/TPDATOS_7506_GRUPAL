/* 
 * File:   Bloque.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 00:16
 */

#ifndef BLOQUE_H
#define	BLOQUE_H

#include "iBloque.h"
#include <stddef.h>

class Bloque: public iBloque
{
	private:
		size_t tamanioBloque;
		bool modificado;
		char *buff;
	
	public:
		Bloque(const char *buff, size_t tamanioBloque);
		~Bloque();

		bool FueModificado();
		void BorrarBitModificacion();

		void LeerBloque(const char *buff);
		void EscribirBloque(char *buff);

		void Dispose();

	private:

};

#endif	/* BLOQUE_H */

