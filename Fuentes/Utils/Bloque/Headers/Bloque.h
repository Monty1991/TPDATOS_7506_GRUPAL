/* 
 * File:   Bloque.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 00:16
 */

#ifndef BLOQUE_H
#define	BLOQUE_H

#include "iBloque.h"

class Bloque: public iBloque
{
	private:
		size_t tamanioBloque;
		bool modificado;
		char *buff;
	
	public:
		Bloque(const char *buff, size_t tamanioBloque);
		~Bloque();

		size_t ObtenerTamanioBloque();

		bool FueModificado();
		void BorrarBitModificacion();

		void LeerBloque(char *buff, size_t offset, size_t length);
		void EscribirBloque(const char *buff, size_t offset, size_t length);

		iBloquePtr Clone();
		void Dispose();

	private:

};

#endif	/* BLOQUE_H */
