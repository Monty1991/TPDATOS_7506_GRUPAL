/* 
 * File:   ArchivoBloque.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 02:08
 */

#ifndef ARCHIVOBLOQUE_H
#define	ARCHIVOBLOQUE_H

#include "../../Archivo/ArchivoFactory.h"
#include "iArchivoBloque.h"

class ArchivoBloque: public iArchivoBloque
{
	private:
		iArchivoPtr archivo;
		size_t tamanioBloque;

	public:
		ArchivoBloque(const char *nombre, size_t tamanioBloque);
		~ArchivoBloque();

		size_t ObtenerTamanioBloque();

		iBloquePtr LeerBloque(size_t nroBloque);
		void EscribirBloque(size_t nroBloque, iBloquePtr bloque);
		
		void Close();
	private:

};

#endif	/* ARCHIVOBLOQUE_H */

