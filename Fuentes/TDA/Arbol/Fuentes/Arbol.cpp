/* 
 * File:   Arbol.cpp
 * Author: Monty
 * 
 * Created on 21 de marzo de 2016, 12:56
 */

#include "../Headers/Arbol.h"

Arbol::Arbol(iFeaturePtr clave, iObjectPtr valor)
{
	this->clave = clave;
	this->valor = valor;
	this->altura = 1;
	this->izq = 0;
	this->der = 0;
}

Arbol::~Arbol()
{
	this->clave->Dispose();
}

Arbol *Arbol::Add(iFeaturePtr clave, iObjectPtr *valor)
{
	int comparacion = this->clave->Comparar(clave);

	if (comparacion > 0)
	{
		if (this->izq)
			this->izq = this->izq->Add(clave, valor);
		else
			this->izq = new Arbol(clave, *valor);

		this->RecalcularAltura();
		return this->Rebalancear();
	}
	else if (comparacion < 0)
	{
		if (this->der)
			this->der = this->der->Add(clave, valor);
		else
			this->der = new Arbol(clave, *valor);

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

iFeaturePtr Arbol::GetKey()
{
	return this->clave;
}

iObjectPtr Arbol::GetValue(iFeaturePtr clave)
{
	int comparacion = this->clave->Comparar(clave);
	
	if (comparacion > 0)
	{
		if (this->izq)
			return this->izq->GetValue(clave);

		return NULL;
	}
	else if (comparacion < 0)
	{
		if (this->der)
			return this->der->GetValue(clave);

		return NULL;
	}

	return this->valor;
}

Arbol *Arbol::Remove(iFeaturePtr clave, iObjectPtr *valor)
{
	int comparacion = this->clave->Comparar(clave);
	if (!comparacion)
	{
		*valor = this->valor;

		if (!this->izq && ! this->der)
		{
			return NULL; // el padre se encarga de borrarlo
		}
		else if (!this->der)
		{
			iArbolPtr heredero = this->izq;
			this->izq = NULL;
			return heredero;
		}
		else if (!this->izq)
		{
			iArbolPtr heredero = this->izq;
			this->izq = NULL;
			return heredero;
		}
		else
		{
			int pendiente = this->CalcularPendiente();
			
			if (pendiente > 0)
			{
				Arbol *sucesor = this->izq;
				sucesor->der = this->der;
			}
		}
		
	}

	Arbol *arbol;
	if (comparacion > 0)
	{
		arbol = this->izq->Remove(clave, valor);
		if (arbol == NULL)
		{
			this->izq->Dispose();
			this->izq = NULL;
		}

		this->RecalcularAltura();
		this->Rebalancear();
	}
	else
	{
		arbol = this->der->Remove(clave, valor);
		if (arbol == NULL)
		{
			this->der->Dispose();
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
