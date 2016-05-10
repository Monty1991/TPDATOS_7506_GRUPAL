#include "../Headers/Nodo.h"

Nodo::Nodo(eTipoNodo tipo, iRegistroPtr *listaRegistros, size_t cantidadRegistros): tipo(tipo)
{
	this->tamanio = 16;
	// con esto nos aseguramos de que la tabla sea potencia de 2
	while (this->tamanio < cantidadRegistros)
		this->tamanio *= 2;

	this->cantidad = cantidadRegistros;
	
	this->tablaRegistros = new iRegistroPtr[this->cantidad];

	for (size_t i = 0; i < cantidadRegistros; i++)
		this->tablaRegistros[i] = listaRegistros[i]->Copiar();
}

Nodo::~Nodo()
{
	if (this->tablaRegistros)
	{
		for (size_t i = 0; i < this->cantidad; i++)
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

size_t Nodo::ObtenerCantidadRegistros()
{
	return this->cantidad;
}

iRegistroPtr Nodo::ObtenerRegistro(size_t pos)
{
	if (pos < this->cantidad)
		return this->tablaRegistros[pos];

	// TODO: lanzar excepcion
	return NULL;
}

iRegistroPtr Nodo::AgregarRegistro(iRegistroPtr reg)
{
	// TODO: Que busque primero si ya esta el registro
	this->tablaRegistros[this->cantidad++] = reg;
	if (this->cantidad >= this->tamanio)
		int x = 0; //TODO: Agregar metodo ResizeTable

	return NULL;
}

iRegistroPtr Nodo::QuitarRegistro(size_t pos)
{
	if (pos >= this->cantidad)
		return NULL;

	iRegistroPtr reg = this->tablaRegistros[pos];
	this->tablaRegistros[pos] = this->tablaRegistros[--this->cantidad];
	if (this->cantidad <= this->tamanio * 4)
		int x = 0;	//TODO: metodo ResizeTable

	return reg;
}
