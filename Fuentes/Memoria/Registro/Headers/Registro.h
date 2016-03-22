/* 
 * File:   Registro.h
 * Author: Monty
 *
 * Created on 22 de marzo de 2016, 00:42
 */

#ifndef REGISTRO_H
#define	REGISTRO_H

#include "iRegistro.h"

class Registro: public iRegistro
{
	private:
		size_t size;
		iFeaturePtr *tabla;
	
	public:
		Registro(size_t size);
		virtual ~Registro();

		size_t GetSize();
		
		iFeaturePtr GetFeature(size_t posicion);
		void SetFeature(size_t posicion, iFeaturePtr feature);

	private:

};

#endif	/* REGISTRO_H */

