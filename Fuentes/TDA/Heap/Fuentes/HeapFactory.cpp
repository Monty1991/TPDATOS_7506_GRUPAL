#include "../HeapFactory.h"
#include "../Headers/Heap.h"

iHeapPtr HeapFactory_Nuevo(tComparador comparador)
{
	return new Heap(comparador);
}
