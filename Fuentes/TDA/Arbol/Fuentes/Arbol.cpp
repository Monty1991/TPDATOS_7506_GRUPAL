/* 
 * File:   Arbol.cpp
 * Author: Monty
 * 
 * Created on 21 de marzo de 2016, 12:56
 */

#include "../Headers/Arbol.h"

Arbol::Arbol(int clave, iObjectPtr valor): clave(clave), valor(valor), altura(1), der(0), izq(0)
{
}

Arbol::~Arbol()
{
}

Arbol *Arbol::Add(int key, iObjectPtr *valor)
{
	if (key < this->clave)
	{
		if (this->izq)
			this->izq = this->izq->Add(key, valor);
		else
			this->izq = new Arbol(key, *valor);

		this->RecalcularAltura();
		return this->Rebalancear();
	}
	else if (key > this->clave)
	{
		if (this->der)
			this->der = this->der->Add(key, valor);
		else
			this->der = new Arbol(key, *valor);

		this->RecalcularAltura();
		return this->Rebalancear();
	}

	if (this->valor == *valor)
		return this;

	iObjectPtr oldValue = this->valor;
	this->valor = *valor;
	*valor = oldValue;
	return this;
}

int Arbol::GetKey()
{
	return this->clave;
}

iObjectPtr Arbol::GetValue(int key)
{
	if (key < this->clave)
	{
		if (this->izq)
			return this->izq->GetValue(key);

		return NULL;
	}
	else if (key > this->clave)
	{
		if (this->der)
			return this->der->GetValue(key);

		return NULL;
	}

	return this->valor;
}

Arbol *Arbol::Remove(int key, iObjectPtr *valor)
{
	if (key == this->clave)
	{
		*valor = this->valor;

		return NULL; // el padre se encarga de borrarlo
	}

	Arbol *arbol;
	if (key < this->clave)
	{
		arbol = this->izq->Remove(key, valor);
		if (arbol == NULL)
		{
			delete this->izq;
			this->izq = NULL;
		}

		this->RecalcularAltura();
		this->Rebalancear();
	}
	else
	{
		arbol = this->der->Remove(key, valor);
		if (arbol == NULL)
		{
			delete this->der;
			this->der = NULL;
		}

		this->RecalcularAltura();
		this->Rebalancear();
	}

	return this;
}

void Arbol::Dispose()
{
	if (this->izq)
		this->izq->Dispose();

	if (this->der)
		this->der->Dispose();

	delete this;
}

Arbol *Arbol::NodoIzq()
{
	return this->izq;
}

Arbol *Arbol::NodoDer()
{
	return this->der;
}

size_t Arbol::GetAltura()
{
	return this->altura;
}

Arbol *Arbol::Rebalancear()
{
	int pendiente = this->CalcularPendiente();

	if (pendiente < -1)
	{
		if (this->izq)
			return this->RotarIzquierda();
	}
	else if (pendiente > 1)
	{
		if (this->der)
			return this->RotarDerecha();
	}

	return this;
}

Arbol *Arbol::RotarIzquierda()
{
	Arbol *nodoDer = this->der;

	this->der = nodoDer->NodoIzq();
	nodoDer->izq = this;

	this->RecalcularAltura();
	nodoDer->RecalcularAltura();
	
	return nodoDer;
}

Arbol *Arbol::RotarDerecha()
{
	Arbol *nodoIzq = this->izq;

	this->izq = nodoIzq->NodoDer();
	nodoIzq->der = this;

	this->RecalcularAltura();
	nodoIzq->RecalcularAltura();

	return nodoIzq;
}

int Arbol::CalcularPendiente()
{
	size_t alturaIzq = (this->izq? this->izq->GetAltura() : 0);
	size_t alturaDer = (this->der? this->der->GetAltura() : 0);

	return alturaIzq - alturaDer;	
}

void Arbol::RecalcularAltura()
{
	size_t alturaIzq = (this->izq? this->izq->GetAltura() : 0);
	size_t alturaDer = (this->der? this->der->GetAltura() : 0);

	this->altura = 1 + (alturaIzq > alturaDer? alturaIzq : alturaDer);
}
