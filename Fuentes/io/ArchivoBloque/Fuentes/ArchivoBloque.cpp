/* 
 * File:   ArchivoBloque.cpp
 * Author: Monty
 * 
 * Created on 17 de marzo de 2016, 02:08
 */

#include "../Headers/ArchivoBloque.h"

ArchivoBloque::ArchivoBloque(const char *nombre, size_t tamanioBloque)
{
	this->archivo = ArchivoFactory_Nuevo(nombre, eTipoArchivo::eTipoArchivo_Binario);
	this->tamanioBloque = tamanioBloque;
}

ArchivoBloque::~ArchivoBloque()
{
	this->archivo->Close();
}

void ArchivoBloque::LeerBloque(char *buff, size_t nroBloque)
{
	this->archivo->Seek(nroBloque * this->tamanioBloque);
	this->archivo->Read(buff, this->tamanioBloque);
}

void ArchivoBloque::EscribirBloque(char *buff, size_t nroBloque)
{
	this->archivo->Seek(nroBloque * this->tamanioBloque);
	this->archivo->Write(buff, this->tamanioBloque);
	this->archivo->Flush();
}
