#include "../Headers/Bitacora.h"
#include "../../Archivo/ArchivoFactory.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"

#include <stdarg.h>
#include <time.h>

Bitacora::Bitacora()
{
	this->archivo = ArchivoFactory_Nuevo("log.txt", eTipoArchivo::eTipoArchivo_Log);
}

Bitacora::Bitacora(const char *nombre)
{
	this->archivo = ArchivoFactory_Nuevo(nombre, eTipoArchivo::eTipoArchivo_Log);
}

Bitacora::~Bitacora()
{
	this->archivo->Close();
}

void Bitacora::Close()
{
	delete this;
}

void Bitacora::Log(const char *format)
{
	this->LogTimeStamp();
	this->archivo->Printf(format);
	this->archivo->Flush();
}

void Bitacora::Log(iExceptionPtr exception)
{
	this->LogTimeStamp();
	char cadena[1000];
	StringUtils_Concatenar(cadena, "Excepcion en thread \"main\" %s: %s\n", exception->Header(), exception->Msg());
	this->archivo->Printf(cadena);

	iStackTracePtr stackTrace = exception->ObtenerStackTrace();
	iTraceEntryPtr entry = stackTrace->Pop();

	while(entry)
	{
		char *entrada = entry->ObtenerAsString();
		StringUtils_Concatenar(cadena, "\t\t\t\t\t\t\t\t%s\n", entrada);
		this->archivo->Printf(cadena);
		delete entrada;
		entry->Dispose();

		entry = stackTrace->Pop();
	}

	stackTrace->Dispose();
	this->archivo->Flush();
}

void Bitacora::LogTimeStamp()
{
	time_t x = time(NULL);
	tm *hora = localtime(&x);
	char cadena[1000];

	StringUtils_Concatenar(cadena, "[%04i/%02i/%02i - %02i:%02i:%02i] ", 1900 + hora->tm_year, 1 + hora->tm_mon, hora->tm_mday, hora->tm_hour, hora->tm_min, hora->tm_sec);
	this->archivo->Printf(cadena);
}
