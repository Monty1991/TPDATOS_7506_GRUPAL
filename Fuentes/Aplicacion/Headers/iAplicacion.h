/* 
 * File:   iAplicacion.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 14:44
 */

#ifndef IAPLICACION_H
#define	IAPLICACION_H

typedef class iAplicacion
{
	virtual int main(int argc, char **argv) = 0;
} *iAplicacionPtr;

#endif	/* IAPLICACION_H */
