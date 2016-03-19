#include "../ExceptionFactory.h"
#include "../Headers/Exception.h"

iExceptionPtr ExceptionFactory_Nuevo(const char *exceptionType, const char *msg, const char *fileName, int line, const char *functionName)
{
	return new Exception(exceptionType, msg, fileName, line, functionName);
}
