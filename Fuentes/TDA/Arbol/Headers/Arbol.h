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
		iFeaturePtr clave;
		iObjectPtr valor;
		size_t altura;
		Arbol *izq;
		Arbol *der;
	
		virtual ~Arbol();
	public:
		Arbol(iFeaturePtr clave, iObjectPtr valor);

		virtual Arbol *Add(iFeaturePtr clave, iObjectPtr *valor);
		virtual iFeaturePtr GetKey();
		virtual iObjectPtr GetValue();
		virtual iObjectPtr GetValue(iFeaturePtr key);
		virtual Arbol *Remove(iFeaturePtr key, iObjectPtr *valor);

		virtual void Dispose();

		// Estos metodos se usan internamente, y por tanto, no 
		// se encuentran declarados en la interfaz
		virtual Arbol *NodoIzq();
		virtual Arbol *NodoDer();
		virtual size_t GetAltura();

		// metodos de rebalanceo del arbol
		virtual Arbol *Rebalancear();
		virtual Arbol *RotarIzquierda();
		virtual Arbol *RotarDerecha();

		virtual int CalcularPendiente();
		virtual void RecalcularAltura();
};

#endif	/* ARBOL_H */
