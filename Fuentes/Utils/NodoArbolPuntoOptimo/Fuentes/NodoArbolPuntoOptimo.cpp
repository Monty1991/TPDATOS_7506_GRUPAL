#include "../Headers/NodoArbolPuntoOptimo.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../StringUtils/Headers/StringUtils.h"
#include "../../../Memoria/ContenedorRegistro/ContenedorRegistroFactory.h"

NodoArbolPuntoOptimoNodoHoja::NodoArbolPuntoOptimoNodoHoja(iRegistroPtr *listaRegistros, size_t cantidadRegistros): Object()
{
	this->contenedorRegistros = ContenedorRegistroFactory_Nuevo(listaRegistros, cantidadRegistros);
}

NodoArbolPuntoOptimoNodoHoja::~NodoArbolPuntoOptimoNodoHoja()
{
	if (this->contenedorRegistros)
		this->contenedorRegistros->Dispose();
}

iNodoArbolPuntoOptimo *NodoArbolPuntoOptimoNodoHoja::Copiar()
{
	Object::IncrementarContador();
	return this;
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
	Object::Dispose();
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
	return this->contenedorRegistros->ObtenerCantidadRegistros();
}

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::ObtenerRegistro(size_t posicion)
{
	return this->contenedorRegistros->ObtenerRegistro(posicion);
}

void NodoArbolPuntoOptimoNodoHoja::AgregarRegistro(iRegistroPtr registro)
{
	this->contenedorRegistros->AgregarRegistro(registro);
}

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::QuitarRegistro(size_t posicion)
{
	return this->contenedorRegistros->QuitarRegistro(posicion);
}

iRegistroPtr NodoArbolPuntoOptimoNodoHoja::QuitarRegistro()
{
	return this->contenedorRegistros->QuitarRegistro();
}

size_t NodoArbolPuntoOptimoNodoHoja::BuscarRegistro(iFeaturePtr clave, size_t nroCampoClave)
{
	return this->contenedorRegistros->BuscarRegistro(clave, nroCampoClave);
}

NodoArbolPuntoOptimoNodoInterno::NodoArbolPuntoOptimoNodoInterno(iRegistroPtr *listaRegistros, size_t cantidadRegistros): Object(), pivote(NULL), radio(0), hijoIzquierdo(0), hijoDerecho(0)
{
	this->contenedorRegistros = ContenedorRegistroFactory_Nuevo(listaRegistros, cantidadRegistros);
}

NodoArbolPuntoOptimoNodoInterno::~NodoArbolPuntoOptimoNodoInterno()
{
	if (this->contenedorRegistros)
		this->contenedorRegistros->Dispose();

	if (this->pivote)
		this->pivote->Dispose();
}

iNodoArbolPuntoOptimo *NodoArbolPuntoOptimoNodoInterno::Copiar()
{
	Object::IncrementarContador();
	return this;
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
	Object::Dispose();
}

eTipoArbol NodoArbolPuntoOptimoNodoInterno::ObtenerTipoArbol()
{
	return eTipoArbol::eTipoArbol_ArbolPuntoOptimo;
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
	return this->contenedorRegistros->ObtenerCantidadRegistros();	
}

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::ObtenerRegistro(size_t pos)
{
	return this->contenedorRegistros->ObtenerRegistro(pos);	
}

void NodoArbolPuntoOptimoNodoInterno::AgregarRegistro(iRegistroPtr reg)
{
	this->contenedorRegistros->AgregarRegistro(reg);
}

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::QuitarRegistro(size_t pos)
{
	return this->contenedorRegistros->QuitarRegistro(pos);
}

iRegistroPtr NodoArbolPuntoOptimoNodoInterno::QuitarRegistro()
{
	return this->contenedorRegistros->QuitarRegistro();
}

size_t NodoArbolPuntoOptimoNodoInterno::BuscarRegistro(iFeaturePtr clave, size_t nroCampoClave)
{
	return this->contenedorRegistros->BuscarRegistro(clave, nroCampoClave);
}
