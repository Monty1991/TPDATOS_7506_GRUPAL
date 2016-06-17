#include "../Headers/Heap.h"

Heap::Heap(eHeap tipo): tipo(tipo), tamanio(16), cantidadElementos(0)
{
	this->tabla = new sHeapComponentPtr[this->tamanio];
}

Heap::~Heap()
{
	for(size_t i = 0; i < this->cantidadElementos; i++)
	{
		delete this->tabla[i];
		this->tabla[i] = NULL;
	}

	delete [] this->tabla;
}

void Heap::Dispose()
{
	delete this;
}

void Heap::Push(sHeapComponentPtr elemento)
{
	if (!elemento)
		return;

	this->tabla[this->cantidadElementos++] = elemento;
	if (this->cantidadElementos >= this->tamanio)
		this->Redimensionar(this->tamanio * 2);

	this->OrdenarAscendente(this->cantidadElementos - 1);
}

sHeapComponentPtr Heap::Peek()
{
	if (this->cantidadElementos < 1)
		return NULL;

	return this->tabla[0];
}

sHeapComponentPtr Heap::Pop()
{
	sHeapComponentPtr elemento = this->Peek();
	if (!elemento)
		return NULL;

	if (!--this->cantidadElementos)
		this->tabla[0] = NULL;
	else
		this->tabla[0] = this->tabla[this->cantidadElementos];

	if (this->cantidadElementos <= this->tamanio / 4)
		this->Redimensionar(this->tamanio / 2);

	this->OrdenarDescendente(0);
	
	return elemento;
}

void Heap::Redimensionar(size_t nuevoTamanio)
{
	sHeapComponentPtr *nuevaTabla = new sHeapComponentPtr[nuevoTamanio];

	for(size_t i = 0; i < this->cantidadElementos; i++)
		nuevaTabla[i] = this->tabla[i];

	sHeapComponentPtr *viejaTabla = this->tabla;
	this->tabla = nuevaTabla;
	this->tamanio = nuevoTamanio;

	delete []viejaTabla;
}

void Heap::OrdenarAscendente(size_t obj)
{
	if (obj == 0)
		return;

	size_t padre = this->Padre(obj);
	if (this->func(this->tabla[padre]->valor, this->tabla[obj]->valor) < 1)
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

	if (hijoIzq >= this->cantidadElementos)
		return;

	size_t hijoMayor = hijoIzq;
	if (hijoDer < this->cantidadElementos)
		if (this->func(this->tabla[hijoIzq]->valor, this->tabla[hijoDer]->valor) < 0)
			hijoMayor = hijoDer;

	if (this->func(this->tabla[obj]->valor, this->tabla[hijoMayor]->valor) > -1)
		return;

	this->Intercambiar(obj, hijoMayor);
	this->OrdenarDescendente(hijoMayor);
}

void Heap::Intercambiar(size_t x, size_t y)
{
	sHeapComponentPtr temp = this->tabla[x];
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

int Heap::func(double x, double y)
{
	if (x < y)
		return this->tipo == eHeap::eHeap_Minimo? -1 : 1;

	if (x > y)
		return this->tipo == eHeap::eHeap_Minimo? 1 : -1;

	return 0;
}
