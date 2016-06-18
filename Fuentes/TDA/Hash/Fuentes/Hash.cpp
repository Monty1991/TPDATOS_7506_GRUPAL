#include "../Headers/Hash.h"
#include "../../Arbol/ArbolFactory.h"

#include <stddef.h>

Hash::Hash()
{
	this->cantidadElementos = 0;
	this->tamanioTabla = 16;
	this->tabla = new iArbolPtr[this->tamanioTabla];

	for(size_t i = 0; i < this->tamanioTabla; i++)
		this->tabla[i] = NULL;
}

Hash::~Hash()
{
	for (size_t i = 0; i < this->cantidadElementos; i++)
	{
		iObjectPtr obj = this->tabla[i];
		if (obj)
			obj->Dispose();
	}

	delete[] this->tabla;
}

void Hash::Dispose()
{
	delete this;
}

bool Hash::Guardar(iObjectPtr obj, iFeaturePtr clave)
{
	size_t posicion = clave->GenerarHash() % this->tamanioTabla;

	if (!this->tabla[posicion])
	{
		this->tabla[posicion] = ArbolFactory_Nuevo(clave->Copiar(), obj);
		this->cantidadElementos++;
	}

	iArbolPtr arbol = this->tabla[posicion];
	if (arbol->GetValue(clave))
		return false;

	this->tabla[posicion] = arbol->Add(clave->Copiar(), &obj);
	this->cantidadElementos++;

	if ((this->cantidadElementos * 1.0)/(this->tamanioTabla) >= 0.8)
		this->Redimensionar(this->tamanioTabla * 2);

	return true;
}

iObjectPtr Hash::Obtener(iFeaturePtr clave)
{
	size_t posicion = clave->GenerarHash() % this->tamanioTabla;
	if (!this->tabla[posicion])
		return NULL;

	iArbolPtr arbol = this->tabla[posicion];
	return arbol->GetValue(clave);
}

iObjectPtr Hash::Borrar(iFeaturePtr clave)
{
	size_t posicion = clave->GenerarHash() % this->tamanioTabla;
	if (!this->tabla[posicion])
		return NULL;

	iArbolPtr arbol = this->tabla[posicion];

	iObjectPtr obj;
	iArbolPtr nuevaRaiz = arbol->Remove(clave, &obj);
	if (nuevaRaiz != arbol)
	{
		arbol->Dispose();
		this->tabla[posicion] = nuevaRaiz;
	}

	if (obj)
		this->cantidadElementos--;

	if ((this->cantidadElementos * 1.0)/(this->tamanioTabla) <= 0.2)
		this->Redimensionar(this->tamanioTabla / 2);

	return obj;
}

size_t Hash::ObtenerCantidad()
{
	return this->cantidadElementos;
}

void Hash::Redimensionar(size_t nuevoTamanio)
{
	iObjectPtr *nuevaTabla = new iObjectPtr[nuevoTamanio];

	for(size_t i = 0; i < this->cantidadElementos; i++)
		nuevaTabla[i] = this->tabla[i];
	
	iObjectPtr *viejaTabla = this->tabla;
	this->tabla = nuevaTabla;
	delete [] viejaTabla;
	
	this->tamanioTabla = nuevoTamanio;
}
