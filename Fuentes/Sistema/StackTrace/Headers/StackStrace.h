/* 
 * File:   StackStrace.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 13:55
 */

#ifndef STACKSTRACE_H
#define	STACKSTRACE_H

#include "iStackTrace.h"
#include "../../../TDA/LinkedList/Headers/iLinkedList.h"
#include <stddef.h>

class StackTrace: public iStackTrace
{
	private:
		iLinkedListPtr stack;

	public:
		StackTrace();
		virtual ~StackTrace();

		void Push(iTraceEntryPtr traceEntry);
		iTraceEntryPtr Pop();

		char *GetAsString();

		StackTrace *Clone();
		virtual void Dispose();
	
	private:
		size_t Count();

};

#endif	/* STACKSTRACE_H */
