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

StackTrace::StackTrace()
{
	this->size = 16;
	this->count = 0;
	this->stack = new iTraceEntryPtr[this->size];
}

StackTrace::~StackTrace()
{
	for(int i = 0; i < this->count; i++)
		this->stack[i]->Dispose();

	delete this->stack;
}

void StackTrace::Push(iTraceEntryPtr traceEntry)
{
	this->stack[this->count++] = traceEntry;
	if (this->count >= this->size)
		this->Resize(this->size * 2);
}

iTraceEntryPtr StackTrace::Pop()
{
	if (!this->count)
		return NULL;

	iTraceEntryPtr traceEntry = this->stack[--this->count];
	this->stack[this->count] = 0;
	
	if (this->count * 4 <= this->size)
		this->Resize(this->size / 2);

	return traceEntry;
}

char *StackTrace::GetAsString()
{
	char *cadena = new char[this->count * 500 + 1];
	cadena[0] = '\0';
	int pos = 0;

	for (int i = this->count - 1;  i >= 0; i--)
	{
		iTraceEntryPtr entry = this->stack[i];
		char *cadenaEntry = entry->ObtenerAsString();
		pos = StringUtils_Concatenar(cadena + pos, "\t\t\t\t\t\t\t\t%s\n", entry->ObtenerAsString());
		delete cadenaEntry;
	}

	char *cadenaFinal = StringUtils_Clonar(cadena);
	delete cadena;

	return cadenaFinal;
}

StackTrace *StackTrace::Clone()
{
	StackTrace *clone = new StackTrace();

	for (int i = 0; i < this->count; i++)
	{
		iTraceEntryPtr entry = this->stack[i];
		clone->Push(entry->Clone());
	}
	
	return clone;
}

void StackTrace::Dispose()
{
	delete this;
}

void StackTrace::Resize(int newSize)
{
	iTraceEntryPtr *newStack = new iTraceEntryPtr[newSize];
	
	for (int i = 0; i < this->count; i++)
		newStack[i] = this->stack[i];
	
	iTraceEntryPtr *oldStack = this->stack;
	this->stack = newStack;
	this->size = newSize;

	delete oldStack;
}
