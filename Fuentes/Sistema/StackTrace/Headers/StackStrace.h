/* 
 * File:   StackStrace.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 13:55
 */

#ifndef STACKSTRACE_H
#define	STACKSTRACE_H

#include "../../TraceEntry/Headers/iTraceEntry.h"
#include "iStackTrace.h"

class StackTrace: public iStackTrace
{
	private:
		iTraceEntryPtr *stack;
		int count;
		int size;

	public:
		StackTrace();
		~StackTrace();

		void Push(iTraceEntryPtr traceEntry);
		iTraceEntryPtr Pop();

		char *GetAsString();

		StackTrace *Clone();
		void Dispose();
	
	private:
		void Resize(int newSize);
};

#endif	/* STACKSTRACE_H */
