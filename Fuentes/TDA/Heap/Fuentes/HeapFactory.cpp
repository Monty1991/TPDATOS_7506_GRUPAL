#include "../HeapFactory.h"
#include "../Headers/Heap.h"

iHeapPtr HeapFactory_Nuevo(eHeap tipo)
{
	return new Heap(tipo);
}
