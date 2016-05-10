/* 
 * File:   Registro.h
 * Author: Monty
 *
 * Created on 22 de marzo de 2016, 00:42
 */

#ifndef REGISTRO_H
#define	REGISTRO_H

#include "iRegistro.h"
#include "../../Object/Headers/Object.h"

class Registro: public iRegistro, public Object
{
	private:
		size_t cantidadCampos;
		iFeaturePtr *tabla;
	
		virtual ~Registro();
	public:
		Registro(size_t cantidadCampos);

		virtual iRegistroPtr Copiar();
		virtual iRegistroPtr Clone();

		virtual size_t ObtenerCantidadCampos();
		
		virtual iFeaturePtr GetFeature(size_t posicion);
		virtual void SetFeature(size_t posicion, iFeaturePtr feature);

		virtual void Dispose();
	private:

};

#endif	/* REGISTRO_H */
