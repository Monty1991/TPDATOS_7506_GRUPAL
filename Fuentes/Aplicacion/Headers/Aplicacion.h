/* 
 * File:   Aplicacion.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 14:45
 */

#ifndef APLICACION_H
#define	APLICACION_H

#include "iAplicacion.h"

class Aplicacion: public iAplicacion
{
	public:
		Aplicacion();
		virtual ~Aplicacion();
		
		int main(int argc, char **argv);

};

#endif	/* APLICACION_H */
