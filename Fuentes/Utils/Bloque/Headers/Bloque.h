/* 
 * File:   Bloque.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 00:16
 */

#ifndef BLOQUE_H
#define	BLOQUE_H

#include "iBloque.h"
#include "../../../Memoria/Object/Headers/Object.h"

class Bloque: public iBloque, public Object
{
	private:
		size_t tamanioBloque;
		bool modificado;
		char *buff;
	
		virtual ~Bloque();
	public:
		Bloque(const char *buff, size_t tamanioBloque);

		virtual iBloquePtr Copiar();
		virtual iBloquePtr Clone();
		virtual size_t ObtenerTamanioBloque();

		virtual bool FueModificado();
		virtual void BorrarBitModificacion();

		virtual const char *ObtenerContenido();

		virtual void LeerBloque(char *buff, size_t offset, size_t length);
		virtual void EscribirBloque(const char *buff, size_t offset, size_t length);

		virtual void Dispose();

	private:

};

#endif	/* BLOQUE_H */
