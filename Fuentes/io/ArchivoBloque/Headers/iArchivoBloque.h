/* 
 * File:   iArchivoBloque.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 02:12
 */

#ifndef IARCHIVOBLOQUE_H
#define	IARCHIVOBLOQUE_H

typedef class iArchivoBloque
{
	public:
		
		virtual void LeerBloque(char *buff, size_t nroBloque) = 0;
		virtual void EscribirBloque(char *buff, size_t nroBloque) = 0;
} *iArchivoBloquePtr;

#endif	/* IARCHIVOBLOQUE_H */
