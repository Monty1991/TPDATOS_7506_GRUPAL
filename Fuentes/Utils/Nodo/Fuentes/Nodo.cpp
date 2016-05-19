#include "../Headers/Nodo.h"
#include "../../StringUtils/Headers/StringUtils.h"
#include "../../../Exceptions/ExceptionFactory.h"

Nodo::Nodo(eTipoNodo tipo, iRegistroPtr *listaRegistros, size_t cantidadRegistro, size_t pivote, float radio): tipo(tipo), pivote(pivote), radio(radio)
{
	this->tamanio = 16;
	// con esto nos aseguramos de que la tabla sea potencia de 2
	while (this->tamanio < cantidadRegistros)
		this->tamanio *= 2;

	this->cantidadRegistros = cantidadRegistros;

	this->tablaRegistros = new iRegistroPtr[this->tamanio];

	for (size_t i = 0; i < cantidadRegistros; i++)
		this->tablaRegistros[i] = listaRegistros[i]->Copiar();
}

Nodo::~Nodo()
{
	if (this->tablaRegistros)
	{
		for (size_t i = 0; i < this->cantidadRegistros; i++)
		{
			if (this->tablaRegistros[i])
			{
				this->tablaRegistros[i]->Dispose();
				this->tablaRegistros[i] = NULL;
			}
		}
	}

	delete[] this->tablaRegistros;
	this->tablaRegistros = NULL;
}

void Nodo::Dispose()
{
	delete this;
}

eTipoNodo Nodo::ObtenerTipoNodo()
{
	return this->tipo;
}

void Nodo::CambiarTipoNodo(eTipoNodo nuevoTipo)
{
	this->tipo = nuevoTipo;
}

size_t Nodo::ObtenerPivote()
{
	return this->pivote;
}

float Nodo::ObtenerRadio()
{
	return this->radio;
}


size_t Nodo::ObtenerCantidadRegistros()
{
	return this->cantidadRegistros;
}

iRegistroPtr Nodo::ObtenerRegistro(size_t pos)
{
	if (pos >= this->cantidadRegistros)
	{
		char msg[20];
		StringUtils_Concatenar(msg, "%lu", pos);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}

	return this->tablaRegistros[pos];
}

iRegistroPtr Nodo::AgregarRegistro(iRegistroPtr reg)
{
	iRegistroPtr old = this->QuitarRegistro(reg->GetFeature(0)->AsNumber().entero.enteroSinSigno.entero32SinSigno);

	this->tablaRegistros[this->cantidadRegistros++] = reg;
	if (this->cantidadRegistros >= this->tamanio)
		this->RedimensionarTabla(this->tamanio * 2);

	return old;
}

iRegistroPtr Nodo::QuitarRegistro(size_t clave)
{
	iRegistroPtr reg = NULL;
	size_t pos;
	for (pos = 0; pos < this->cantidadRegistros; pos++)
		if (this->tablaRegistros[pos]->GetFeature(0)->AsNumber().entero.enteroSinSigno.entero32SinSigno == clave)
			break;

	if (pos >= this->cantidadRegistros)
		return NULL;

	reg = this->tablaRegistros[pos];
	this->tablaRegistros[pos] = this->tablaRegistros[--this->cantidadRegistros];
	if (this->cantidadRegistros <= this->tamanio * 4)
		this->RedimensionarTabla(this->tamanio / 2);

	return reg;
}

void Nodo::RedimensionarTabla(size_t nuevoTamanio)
{
	iRegistroPtr *nuevaTabla = new iRegistroPtr[nuevoTamanio];

	for (size_t i = 0; i < this->cantidadRegistros; i++)
		nuevaTabla[i] = this->tablaRegistros[i];

	delete [] this->tablaRegistros;
	this->tablaRegistros = nuevaTabla;
	this->tamanio = nuevoTamanio;
}
