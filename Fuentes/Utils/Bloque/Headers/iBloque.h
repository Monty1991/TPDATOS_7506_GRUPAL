/* 
 * File:   iBloque.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 00:25
 */

#ifndef IBLOQUE_H
#define	IBLOQUE_H

typedef class iBloque
{
	public:
		virtual bool FueModificado() = 0;
		virtual void BorrarBitModificacion() = 0;

		virtual void LeerBloque(char *buff) = 0;
		virtual void EscribirBloque(const char *buff) = 0;

		virtual void Dispose() = 0;

} *iBloquePtr;

#endif	/* IBLOQUE_H */
