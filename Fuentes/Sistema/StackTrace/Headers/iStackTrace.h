/* 
 * File:   iStackTrace.h
 * Author: Monty
 *
 * Created on 18 de marzo de 2016, 05:38
 */

#ifndef ISTACKTRACE_H
#define	ISTACKTRACE_H

#include "../../TraceEntry/Headers/iTraceEntry.h"

typedef class iStackTrace
{
	public:

		virtual void Push(iTraceEntryPtr entryPtr) = 0;
		virtual iTraceEntryPtr Pop() = 0;

		virtual char *GetAsString() = 0;
		
		virtual iStackTrace *Clone() = 0;
		virtual void Dispose() = 0;
} *iStackTracePtr;

#endif	/* ISTACKTRACE_H */
