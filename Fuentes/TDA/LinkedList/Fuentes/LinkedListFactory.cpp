#include "../LinkedListFactory.h"
#include "../Headers/LinkedList.h"

iLinkedListPtr LinkedListFactory_Nuevo(iObjectPtr obj, iLinkedListPtr next)
{
	return new LinkedList(obj, next);
}
