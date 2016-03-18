#include "../TraceEntryFactory.h"
#include "../Headers/TraceEntry.h"

iTraceEntryPtr TraceEntryFactory_Nuevo(const char *fileName, int line, const char *functionName)
{
	return new TraceEntry(fileName, line, functionName);
}
