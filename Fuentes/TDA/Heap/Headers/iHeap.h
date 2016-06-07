/* 
 * File:   iHeap.h
 * Author: Monty
 *
 * Created on 7 de junio de 2016, 01:40
 */

#ifndef IHEAP_H
#define IHEAP_H

#include "../../../Memoria/Object/Headers/iObject.h"

enum eHeap
{
	eHeap_Minimo,
	eHeap_Maximo
};

typedef struct sHeapComponent
{
	float valor;
	iObjectPtr object;
} *sHeapComponentPtr;

typedef class iHeap
{
	public:
		virtual void Dispose() = 0;

		virtual void Push(sHeapComponentPtr value) = 0;
		virtual sHeapComponentPtr Peek() = 0;
		virtual sHeapComponentPtr Pop() = 0;
		
} *iHeapPtr;

#endif /* IHEAP_H */
