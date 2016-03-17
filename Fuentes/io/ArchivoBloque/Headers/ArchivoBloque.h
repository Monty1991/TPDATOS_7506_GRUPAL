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

		void LeerBloque(char *buff, size_t nroBloque);
		void EscribirBloque(char *buff, size_t nroBloque);
		
	private:

};

#endif	/* ARCHIVOBLOQUE_H */

