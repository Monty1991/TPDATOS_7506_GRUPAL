/* 
 * File:   iHeap.h
 * Author: Monty
 *
 * Created on 10 de abril de 2016, 00:52
 */

#ifndef IHEAP_H
#define	IHEAP_H

typedef int (*tComparador)(void *, void *);

typedef class iHeap
{
	public:
		virtual void *Pop() = 0;
		virtual void Push(void *elemento) = 0;

		virtual void Dispose() = 0;

} *iHeapPtr;

#endif	/* IHEAP_H */

