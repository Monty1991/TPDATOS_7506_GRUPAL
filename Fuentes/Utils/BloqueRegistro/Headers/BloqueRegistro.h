/* 
 * File:   BloqueRegistro.h
 * Author: Monty
 *
 * Created on 1 de abril de 2016, 00:23
 */

#ifndef BLOQUEREGISTRO_H
#define	BLOQUEREGISTRO_H

#include "../../../TDA/Arbol/Headers/iArbol.h"
#include "iBloqueRegistro.h"

class BloqueRegistro: public iBloqueRegistro
{
	private:
		iArbolPtr contenedor;
	
	public:
		BloqueRegistro();
		virtual ~BloqueRegistro();

		void AgregarRegistro(int idRegistro, iRegistroPtr *registro);
		iRegistroPtr ObtenerRegistro(int idRegistro);
		iRegistroPtr RemoverRegistro(int idRegistro);

		void Dispose();

	private:

};

#endif	/* BLOQUEREGISTRO_H */

