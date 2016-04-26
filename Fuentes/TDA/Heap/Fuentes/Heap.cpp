#include "../Headers/Heap.h"

Heap::Heap(tComparador func): tamanio(16), func(func), cantidadElementos(0)
{
	this->tabla = new void *[this->tamanio];
}

Heap::~Heap()
{
	for (size_t i = 0; i < this->cantidadElementos; i++)
	{
		if (this->tabla[i])
		{	
			delete this->tabla[i];
			this->tabla[i] = NULL;
		}
	}

	delete [] this->tabla;
}

void Heap::Push(void *elemento)
{
	this->tabla[this->cantidadElementos++] = elemento;
	if (this->cantidadElementos >= this->tamanio)
		this->Redimensionar(this->tamanio * 2);

	this->OrdenarAscendente(this->cantidadElementos - 1);
}

void *Heap::Pop()
{
	if (this->cantidadElementos < 1)
		return NULL;

	void *elemento = this->tabla[0];
	this->tabla[0] = this->tabla[--this->cantidadElementos];
	if (this->cantidadElementos <= this->tamanio / 4)
		this->Redimensionar(this->tamanio / 2);

	this->OrdenarDescendente(0);
	
	return elemento;
}

void Heap::Dispose()
{
	delete this;
}

void Heap::Redimensionar(size_t nuevoTamanio)
{
	void **nuevaTabla = new void *[nuevoTamanio];

	for(size_t i = 0; i < this->cantidadElementos; i++)
		nuevaTabla[i] = this->tabla[i];

	void **viejaTabla = this->tabla;
	this->tabla = nuevaTabla;
	this->tamanio = nuevoTamanio;

	delete []viejaTabla;
}

void Heap::OrdenarAscendente(size_t obj)
{
	if (obj == 0)
		return;

	size_t padre = this->Padre(obj);
	if (this->func(this->tabla[padre], this->tabla[obj]) < 1)
		return;

	this->Intercambiar(padre, obj);
	this->OrdenarAscendente(padre);
}

void Heap::OrdenarDescendente(size_t obj)
{
	if (obj >= this->tamanio)
		return;

	size_t hijoIzq = this->HijoIzq(obj);
	size_t hijoDer = this->HijoDer(obj);

	if (hijoIzq >= this->tamanio)
		return;

	size_t hijoMayor = hijoIzq;
	if (hijoDer < this->tamanio)
		if (this->func(this->tabla[hijoIzq], this->tabla[hijoDer]) < 0)
			hijoMayor = hijoDer;

	if (this->func(this->tabla[obj], this->tabla[hijoMayor]) > -1)
		return;

	this->Intercambiar(obj, hijoMayor);
	this->OrdenarDescendente(hijoMayor);
}

void Heap::Intercambiar(size_t x, size_t y)
{
	void *temp = this->tabla[x];
	this->tabla[x] = this->tabla[y];
	this->tabla[y] = temp;
}

size_t Heap::Padre(size_t obj)
{
	return ((obj - 1 ) / 2) + (obj % 2);
}

size_t Heap::HijoIzq(size_t obj)
{
	return obj * 2 + 1;
}

size_t Heap::HijoDer(size_t obj)
{
	return (obj + 1) * 2;
}
