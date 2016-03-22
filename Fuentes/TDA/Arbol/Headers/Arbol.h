/* 
 * File:   Arbol.h
 * Author: Monty
 *
 * Created on 21 de marzo de 2016, 12:56
 */

#ifndef ARBOL_H
#define	ARBOL_H

#include "iArbol.h"

#include <stddef.h>

class Arbol: public iArbol
{
	private:
		int clave;
		iObjectPtr valor;
		size_t altura;
		Arbol *izq;
		Arbol *der;
	
	public:
		Arbol(int clave, iObjectPtr valor);
		virtual ~Arbol();

		Arbol *Add(int key, iObjectPtr *valor);
		int GetKey();
		iObjectPtr GetValue();
		iObjectPtr GetValue(int key);
		Arbol *Remove(int key, iObjectPtr *valor);

		void Dispose();

		// Estos metodos se usan internamente, y por tanto, no 
		// se encuentran declarados en la interfaz
		Arbol *NodoIzq();
		Arbol *NodoDer();
		size_t GetAltura();

		// metodos de rebalanceo del arbol
		Arbol *Rebalancear();
		Arbol *RotarIzquierda();
		Arbol *RotarDerecha();

		int CalcularPendiente();
		void RecalcularAltura();
};

#endif	/* ARBOL_H */
