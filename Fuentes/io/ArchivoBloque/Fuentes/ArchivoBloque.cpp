/* 
 * File:   ArchivoBloque.cpp
 * Author: Monty
 * 
 * Created on 17 de marzo de 2016, 02:08
 */

#include "../Headers/ArchivoBloque.h"
#include "../../../Utils/Bloque/BloqueFactory.h"

ArchivoBloque::ArchivoBloque(const char *nombre, size_t tamanioBloque): tamanioBloque(tamanioBloque)
{
	this->archivo = ArchivoFactory_Nuevo(nombre, eTipoArchivo::eTipoArchivo_Binario);

	// nos aseguramos de que el bloque 0 siempre exista
	if ((size_t)this->archivo->GetFileSize() < this->tamanioBloque)
	{
		char buff[this->tamanioBloque];
		for (size_t i = 0; i < this->tamanioBloque; i++)
			buff[i] = 0;

		iBloquePtr bloque = BloqueFactory_Nuevo(buff, this->tamanioBloque);

		this->EscribirBloque(0, bloque);
		bloque->Dispose();
	}
}

ArchivoBloque::~ArchivoBloque()
{
	this->archivo->Close();
}

size_t ArchivoBloque::ObtenerTamanioBloque()
{
	return this->tamanioBloque;
}

iBloquePtr ArchivoBloque::LeerBloque(size_t nroBloque)
{
	this->archivo->Seek(nroBloque * this->tamanioBloque);

	char buff[this->tamanioBloque];
	for (size_t i = 0; i < this->tamanioBloque; i++)	// por las dudas
		buff[i] = 0;

	this->archivo->Read(buff, this->tamanioBloque);
	return BloqueFactory_Nuevo(buff, this->tamanioBloque);
}

void ArchivoBloque::EscribirBloque(size_t nroBloque, iBloquePtr bloque)
{
	this->archivo->Seek(nroBloque * this->tamanioBloque);

	this->archivo->Write(bloque->ObtenerContenido(), this->tamanioBloque);
	this->archivo->Flush();
}

void ArchivoBloque::Close()
{
	delete this;
}
