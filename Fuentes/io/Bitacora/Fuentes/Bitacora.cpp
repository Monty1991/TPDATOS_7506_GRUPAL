#include "../Headers/Bitacora.h"
#include "../../Archivo/ArchivoFactory.h"

#include <stdio.h>

Bitacora::Bitacora()
{
	this->archivo = ArchivoFactory_Nuevo("asdf");
//	this->file = fopen("asdf", "a+");
}

Bitacora::Bitacora(const char *nombre)
{
	this->archivo = ArchivoFactory_Nuevo("nombre");
//	this->file = fopen(file, "a+");
}

Bitacora::~Bitacora()
{
/*	if (this->file)
	{
		fflush(this->file);
		fclose(this->file);
	}
*/
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

//	fprintf(this->file, string);
//	fflush(this->file);
}

void Bitacora::Log(long valor)
{
	this->archivo->Printf("%i", valor);
	this->archivo->Flush();

//	fprintf(this->file, "%i", valor);
//	fflush(this->file);
}

void Bitacora::Log(double valor)
{
	this->archivo->Printf("%f", valor);
	this->archivo->Flush();

//	fprintf(this->file, "%f", valor);
//	fflush(this->file);
}
