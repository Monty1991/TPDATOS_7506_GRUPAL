/* 
 * File:   Heap.h
 * Author: Monty
 *
 * Created on 10 de abril de 2016, 00:54
 */

#ifndef HEAP_H
#define	HEAP_H

#include "iHeap.h"

#include <stddef.h>

class Heap: public iHeap
{
	private:
		void **tabla;
		size_t tamanio;
		size_t cantidadElementos;
		tComparador func;

	public:
		Heap(tComparador func);
		virtual ~Heap();
		
		virtual void Push(void *elemento);
		virtual void *Pop();

		virtual void Dispose();

	private:
		void Redimensionar(size_t nuevoTamanio);
		void OrdenarAscendente(size_t obj);
		void OrdenarDescendente(size_t obj);
		void Intercambiar(size_t x, size_t y);
		size_t Padre(size_t obj);
		size_t HijoIzq(size_t obj);
		size_t HijoDer(size_t obj);
};

#endif	/* HEAP_H */
