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
		this->tablaRegistros[i] = listaRegistros[i]->Copiar();
}

NodoArbolPuntoOptimoNodoHoja::~NodoArbolPuntoOptimoNodoHoja()
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

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::AgregarRegistro(iRegistroPtr reg)
{
	iRegistroPtr old = this->QuitarRegistro(reg->GetFeature(0)->AsNumber().entero.enteroSinSigno.entero32SinSigno);

	this->tablaRegistros[this->cantidadRegistros++] = reg;
	if (this->cantidadRegistros >= this->tamanioTablaRegistros)
		this->RedimensionarTabla(this->tamanioTablaRegistros * 2);

	return old;
}

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::QuitarRegistro(size_t clave)
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
	if (this->cantidadRegistros <= this->tamanioTablaRegistros * 4)
		this->RedimensionarTabla(this->tamanioTablaRegistros / 2);

	return reg;
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

NodoArbolPuntoOptimoNodoInterno::NodoArbolPuntoOptimoNodoInterno(iRegistroPtr *listaRegistros, size_t cantidadRegistros): pivote(0), radio(0), hijoIzquierdo(0), hijoDerecho(0)
{
	this->nodoHoja = new NodoArbolPuntoOptimoNodoHoja(listaRegistros, cantidadRegistros);
}

NodoArbolPuntoOptimoNodoInterno::~NodoArbolPuntoOptimoNodoInterno()
{
	if (this->nodoHoja)
		this->nodoHoja->Dispose();
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

size_t NodoArbolPuntoOptimoNodoInterno::ObtenerPivote()
{
	return this->pivote;
}

void NodoArbolPuntoOptimoNodoInterno::EstablecerPivote(size_t pivote)
{
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

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::AgregarRegistro(iRegistroPtr reg)
{
	return this->nodoHoja->AgregarRegistro(reg);
}

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::QuitarRegistro(size_t clave)
{
	return this->nodoHoja->QuitarRegistro(clave);
}
