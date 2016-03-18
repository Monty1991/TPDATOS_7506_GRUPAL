#include "../StackTraceFactory.h"
#include "../Headers/StackStrace.h"

iStackTracePtr StackTraceFactory_Nuevo()
{
	return new StackTrace();
}
