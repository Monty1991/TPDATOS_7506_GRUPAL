/* 
 * File:   iDescriptorRegistro.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 03:48
 */

#ifndef IDESCRIPTORREGISTRO_H
#define	IDESCRIPTORREGISTRO_H

#include "../../../Memoria/Datos.h"

enum eTipoCampo
{
	eTipoCampo_I1,	//	entero con signo 1 byte -> char
	eTipoCampo_I2,	//	entero con signo 2 bytes -> short
	eTipoCampo_I4,	//	entero con signo 4 bytes -> int
	eTipoCampo_I8,	//	entero con signo 8 bytes -> long long
	eTipoCampo_F32,	//	Flotante IEEE754 de 32 bits
	eTipoCampo_F64,	//	Flotante IEEE754 de 64 bits
	eTipoCampo_CX,	//	Cadena de caracteres con prefijo, max 255 caracteres
	eTipoCampo_C0,	//	Cadena de caracteres con terminador nulo
	eTipoCampo_T,	//	Hora, representado por una cadena con formato HHMMSS
	eTipoCampo_D,	//	Fecha, representado por una cadena con formato AAAAMMDD
	eTipoCampo_DT	//	Fecha y hora, representado por: AAAAMMDDHHNNSS
};

typedef class iDescriptorRegistro
{
	public:
		virtual eTipoCampo ObtenerTipoCampo(size_t nroCampo) = 0;
		virtual size_t ObtenerCantidadCampos() = 0;

		virtual void Dispose() = 0;
} *iDescriptorRegistroPtr;

#endif	/* IDESCRIPTORREGISTRO_H */
