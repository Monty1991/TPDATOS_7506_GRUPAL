/* 
 * File:   Heap.h
 * Author: Monty
 *
 * Created on 7 de junio de 2016, 01:39
 */

#ifndef HEAP_H
#define HEAP_H

#include "iHeap.h"
#include <stddef.h>

class Heap: public iHeap
{
	private:
		sHeapComponentPtr *tabla;
		size_t tamanio;
		size_t cantidadElementos;
		eHeap tipo;
		
		virtual ~Heap();
	public:
		Heap(eHeap tipo);

		virtual void Dispose();

		virtual void Push(sHeapComponentPtr value);
		virtual sHeapComponentPtr Peek();
		virtual sHeapComponentPtr Pop();

	private:
		virtual void Redimensionar(size_t nuevoTamanio);
		virtual void OrdenarAscendente(size_t obj);
		virtual void OrdenarDescendente(size_t obj);
		virtual void Intercambiar(size_t x, size_t y);
		virtual size_t Padre(size_t obj);
		virtual size_t HijoIzq(size_t obj);
		virtual size_t HijoDer(size_t obj);

		// para heap de minimo,
		// devuelve < 0 si x < y, 0 si son iguales, > 0 si x > y
		// para heap de maximo, hace lo contrario
		virtual int func(float x, float y);
};

#endif /* HEAP_H */
