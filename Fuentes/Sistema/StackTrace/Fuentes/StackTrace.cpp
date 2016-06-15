/* 
 * File:   StackStrace.cpp
 * Author: Monty
 * 
 * Created on 17 de marzo de 2016, 13:56
 */

#include "../Headers/StackStrace.h"
#include <stdlib.h>
#include "../../TraceEntry/TraceEntryFactory.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"
#include "../../../TDA/LinkedList/LinkedListFactory.h"

StackTrace::StackTrace()
{
	this->stack = NULL;
}

StackTrace::~StackTrace()
{
	while (this->stack)
	{
		iObjectPtr obj = this->Pop();
		if (obj)
			obj->Dispose();
	}
}

void StackTrace::Push(iTraceEntryPtr traceEntry)
{
	iLinkedListPtr currentStack = this->stack? this->stack->Copiar(): NULL;
	this->stack = LinkedListFactory_Nuevo(traceEntry, currentStack);
}

iTraceEntryPtr StackTrace::Pop()
{
	if (!this->stack)
		return NULL;

	iLinkedListPtr listItem = this->stack;

	iTraceEntryPtr traceEntry = (iTraceEntryPtr)listItem->Value();
	if (traceEntry)
		traceEntry = traceEntry->Copiar();

	this->stack = listItem->Next();

	listItem->Dispose();

	return traceEntry;
}

char *StackTrace::GetAsString()
{
	char *cadena = new char[this->Count() * 500 + 1];
	cadena[0] = '\0';
	int pos = 0;

	iLinkedListPtr list = this->stack;
	while (list)
	{
		iTraceEntryPtr entry = (iTraceEntryPtr)list->Value();
		char *cadenaEntry = entry->ObtenerAsString();
		pos = StringUtils_Concatenar(cadena + pos, "\t\t\t\t\t\t\t\t%s\n", cadenaEntry);
		delete[] cadenaEntry;
		list = list->Next();
	}

	char *cadenaFinal = StringUtils_Clonar(cadena);
	delete[] cadena;

	return cadenaFinal;
}

StackTrace *StackTrace::Clone()
{
	StackTrace *clone = new StackTrace();

	// Toda clase es friend consigo misma.
	iLinkedListPtr copia = NULL;
	if (this->stack)
		copia = this->stack->Clone();
	
	clone->stack = copia;

	return clone;
}

void StackTrace::Dispose()
{
	delete this;
}

size_t StackTrace::Count()
{
	size_t count = 0;
	iLinkedListPtr list = this->stack;
	while (list)
	{
		list = list->Next();
		count++;
	}

	return count;
}
