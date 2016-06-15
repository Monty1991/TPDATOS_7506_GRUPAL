#include "../Headers/NodoArbolPuntoOptimo.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../StringUtils/Headers/StringUtils.h"

NodoArbolPuntoOptimoNodoHoja::NodoArbolPuntoOptimoNodoHoja(iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	this->tamanioTablaRegistros = 16;
	// con esto nos aseguramos de que la tabla sea potencia de 2
	while (this->tamanioTablaRegistros < cantidadRegistros)
		this->tamanioTablaRegistros *= 2;

	this->cantidadRegistros = cantidadRegistros;

	this->tablaRegistros = new iRegistroPtr[this->tamanioTablaRegistros];

	for (size_t i = 0; i < cantidadRegistros; i++)
	{
		if (listaRegistros[i])
			this->tablaRegistros[i] = listaRegistros[i];
		else
			this->tablaRegistros[i] = NULL;
	}
}

NodoArbolPuntoOptimoNodoHoja::~NodoArbolPuntoOptimoNodoHoja()
{
	if (this->tablaRegistros)
	{
		for (size_t i = 0; i < this->cantidadRegistros; i++)
		{
			iRegistroPtr reg = this->tablaRegistros[i];
			if (reg)
				reg->Dispose();
		}
	}

	delete[] this->tablaRegistros;
	this->tablaRegistros = NULL;
}

iNodoArbolPuntoOptimo *NodoArbolPuntoOptimoNodoHoja::Clone()
{
	iNodoArbolPuntoOptimoNodoHojaPtr copia = new NodoArbolPuntoOptimoNodoHoja(NULL, 0);
	for (size_t i = 0; i < this->ObtenerCantidadRegistros(); i++)
		{
			iRegistroPtr reg = this->ObtenerRegistro(i);
			if (reg)
				reg = reg->Clone();
			copia->AgregarRegistro(reg);
		}

	return copia;
}

void NodoArbolPuntoOptimoNodoHoja::Dispose()
{
	delete this;
}

eTipoArbol NodoArbolPuntoOptimoNodoHoja::ObtenerTipoArbol()
{
	return eTipoArbol::eTipoArbol_ArbolPuntoOptimo;
}

eNodoArbolPuntoOptimo NodoArbolPuntoOptimoNodoHoja::ObtenerTipoNodo()
{
	return eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja;
}

size_t NodoArbolPuntoOptimoNodoHoja::ObtenerCantidadRegistros()
{
	return this->cantidadRegistros;
}

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::ObtenerRegistro(size_t pos)
{
	if (pos >= this->cantidadRegistros)
	{
		char msg[20];
		StringUtils_Concatenar(msg, "%lu", pos);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}

	return this->tablaRegistros[pos];
}

void NodoArbolPuntoOptimoNodoHoja::AgregarRegistro(iRegistroPtr reg)
{
	this->tablaRegistros[this->cantidadRegistros++] = reg;
	if (this->cantidadRegistros >= this->tamanioTablaRegistros)
		this->RedimensionarTabla(this->tamanioTablaRegistros * 2);
}

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::QuitarRegistro(size_t pos)
{
	if (pos >= this->cantidadRegistros)
		return NULL;

	iRegistroPtr reg = this->tablaRegistros[pos];
	this->cantidadRegistros--;
	for (size_t i = pos; pos < this->cantidadRegistros; i++)
		this->tablaRegistros[i] = this->tablaRegistros[i + 1];

	if (this->cantidadRegistros * 4 <= this->tamanioTablaRegistros)
		this->RedimensionarTabla(this->tamanioTablaRegistros / 2);

	return reg;
}

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::QuitarRegistro()
{
	return this->QuitarRegistro(0);
}

void NodoArbolPuntoOptimoNodoHoja::RedimensionarTabla(size_t nuevoTamanio)
{
	iRegistroPtr *nuevaTabla = new iRegistroPtr[nuevoTamanio];

	for (size_t i = 0; i < this->cantidadRegistros; i++)
		nuevaTabla[i] = this->tablaRegistros[i];

	delete [] this->tablaRegistros;
	this->tablaRegistros = nuevaTabla;
	this->tamanioTablaRegistros = nuevoTamanio;
}

NodoArbolPuntoOptimoNodoInterno::NodoArbolPuntoOptimoNodoInterno(iRegistroPtr *listaRegistros, size_t cantidadRegistros): pivote(NULL), radio(0), hijoIzquierdo(0), hijoDerecho(0)
{
	this->nodoHoja = new NodoArbolPuntoOptimoNodoHoja(listaRegistros, cantidadRegistros);
}

NodoArbolPuntoOptimoNodoInterno::~NodoArbolPuntoOptimoNodoInterno()
{
	if (this->nodoHoja)
		this->nodoHoja->Dispose();

	if (this->pivote)
		this->pivote->Dispose();
}

iNodoArbolPuntoOptimo *NodoArbolPuntoOptimoNodoInterno::Clone()
{
	iNodoArbolPuntoOptimoNodoInternoPtr copia = new NodoArbolPuntoOptimoNodoInterno(NULL, 0);
	for (size_t i = 0; i < this->ObtenerCantidadRegistros(); i++)
		copia->AgregarRegistro(this->ObtenerRegistro(i)->Clone());

	copia->EstablecerPivote(this->ObtenerPivote()->Clone());
	copia->EstablecerRadio(this->ObtenerRadio());
	copia->EstablecerHijoIzquierdo(this->ObtenerHijoIzquierdo());
	copia->EstablecerHijoDerecho(this->ObtenerHijoDerecho());
	
	return copia;
}

void NodoArbolPuntoOptimoNodoInterno::Dispose()
{
	delete this;
}

eTipoArbol NodoArbolPuntoOptimoNodoInterno::ObtenerTipoArbol()
{
	return this->nodoHoja->ObtenerTipoArbol();
}

eNodoArbolPuntoOptimo NodoArbolPuntoOptimoNodoInterno::ObtenerTipoNodo()
{
	return eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno;
}

iFeaturePtr NodoArbolPuntoOptimoNodoInterno::ObtenerPivote()
{
	return this->pivote;
}

void NodoArbolPuntoOptimoNodoInterno::EstablecerPivote(iFeaturePtr pivote)
{
	// Si es el mismo pivote, no tiene sentido reescribir
	if (this->pivote == pivote)
		return;

	if (this->pivote)
		this->pivote->Dispose();

	this->pivote = pivote;
}

float NodoArbolPuntoOptimoNodoInterno::ObtenerRadio()
{
	return this->radio;
}

void NodoArbolPuntoOptimoNodoInterno::EstablecerRadio(float radio)
{
	this->radio = radio;
}

void NodoArbolPuntoOptimoNodoInterno::EstablecerHijoIzquierdo(size_t nodo)
{
	this->hijoIzquierdo = nodo;
}

size_t NodoArbolPuntoOptimoNodoInterno::ObtenerHijoIzquierdo()
{
	return this->hijoIzquierdo;
}

void NodoArbolPuntoOptimoNodoInterno::EstablecerHijoDerecho(size_t nodo)
{
	this->hijoDerecho = nodo;
}

size_t NodoArbolPuntoOptimoNodoInterno::ObtenerHijoDerecho()
{
	return this->hijoDerecho;
}

size_t NodoArbolPuntoOptimoNodoInterno::ObtenerCantidadRegistros()
{
	return this->nodoHoja->ObtenerCantidadRegistros();	
}

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::ObtenerRegistro(size_t pos)
{
	return this->nodoHoja->ObtenerRegistro(pos);	
}

void NodoArbolPuntoOptimoNodoInterno::AgregarRegistro(iRegistroPtr reg)
{
	this->nodoHoja->AgregarRegistro(reg);
}

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::QuitarRegistro(size_t pos)
{
	return this->nodoHoja->QuitarRegistro(pos);
}

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::QuitarRegistro()
{
	return this->nodoHoja->QuitarRegistro();
}

