#include "../Headers/Bitacora.h"
#include "../../Archivo/ArchivoFactory.h"

#include <stdio.h>
#include <stdarg.h>

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

void Bitacora::Log(const char *string)
{
	this->archivo->Printf(string);
	this->archivo->Flush();
}
