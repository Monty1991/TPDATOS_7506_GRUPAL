/*
 * VpTree_ABM.cpp
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#include "../Headers/VpTree_ABM.h"
#include "../../../io/ArchivoArbol/ArchivoArbolFactory.h"
#include "../../../Utils/NodoArbolPuntoOptimo/NodoArbolPuntoOptimoFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Utils/EspacioMetrico/EspacioMetricoFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../Heap/HeapFactory.h"

VpTree_ABM::~VpTree_ABM()
{
	if (this->raiz)
	{
		this->raiz->Dispose();
		this->raiz = NULL;
	}

	if (this->archivo)
	{
		this->archivo->Close();
		this->archivo = NULL;
	}

	if (this->espacioMetrico)
	{
		this->espacioMetrico->Dispose();
		this->espacioMetrico = NULL;
	}
}

void VpTree_ABM::Dispose()
{
	delete this;
}

void VpTree_ABM::Escribir(size_t _nroNodo, iNodoArbolPuntoOptimoPtr _nodo)
{
	if (!_nroNodo && (_nodo != this->raiz))
	{
		iNodoPtr viejaRaiz = this->raiz;
		this->raiz = _nodo->Clone();

		if (viejaRaiz)
			viejaRaiz->Dispose();
	}

	this->archivo->EscribirNodo(_nroNodo, _nodo);
}

float VpTree_ABM::Distancia(iFeaturePtr _key1, iFeaturePtr _key2)
{
	if (!_key1)
		Throw(ExceptionType_InvalidArg, "_key1 == NULL");

	if (!_key2)
		Throw(ExceptionType_InvalidArg, "_key2 == NULL");

	if (_key1->ObtenerTipo() != _key2->ObtenerTipo())
		Throw(ExceptionType_InvalidArg, "_key1->Tipo != _key2->Tipo");

	// numerico -> usar claves numericas
	if (_key1->ObtenerTipo() & Mascara_Numero)
		return this->espacioMetrico->CalcularDistancia(
				_key1->AsNumber().entero.enteroSinSigno.entero32SinSigno,
				_key2->AsNumber().entero.enteroSinSigno.entero32SinSigno);

	// no numerico -> usar claves de cadenas
	if (!(_key1->ObtenerTipo() & Mascara_Numero))
		return this->espacioMetrico->CalcularDistancia(_key1->AsCadenaANSI(),
				_key2->AsCadenaANSI());

	Throw(ExceptionType_InvalidArg, "_key1->Tipo not supported");
}

VpTree_ABM::VpTree_ABM(const char* _fileName, size_t _nroCampoClave, size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia): nroCampoClave(_nroCampoClave)
{
	this->espacioMetrico = EspacioMetricoFactory_Nuevo();

	this->archivo = ArchivoArbolFactory_Nuevo(_fileName, _tamanioNodo, _cargaMinima, _tolerancia, eTipoArbol_ArbolPuntoOptimo);

	this->raiz = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(0);

	if (this->raiz == NULL) {

		this->raiz = NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo_Hoja);
		this->Escribir(0, raiz);
	}
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoPadre, iNodoArbolPuntoOptimoNodoInternoPtr _padre)
{
	size_t nroNodoHijo = _padre->ObtenerHijoDerecho();

	if (!nroNodoHijo)
		if (!(nroNodoHijo = _padre->ObtenerHijoIzquierdo()))
			Throw(" ", "Nodo interno sin hijos.");

	iNodoArbolPuntoOptimoPtr hijo = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(nroNodoHijo);

	if ((hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja) && (archivo->DeterminarEstadoNodo(hijo) == eEstadoCargaNodo_CargaMinima))
	{
		iNodoArbolPuntoOptimoPtr padreNuevo = this->Fusionar(_padre, nroNodoHijo, (iNodoArbolPuntoOptimoNodoHojaPtr) hijo);

		this->archivo->LiberarNodo(nroNodoHijo);
		this->Escribir(_nroNodoPadre, padreNuevo);

		padreNuevo->Dispose();
	}
	else
	{
		while (this->archivo->DeterminarEstadoNodo(_padre) == eEstadoCargaNodo_Underflow)
			_padre->AgregarRegistro(hijo->QuitarRegistro());

		if (this->archivo->DeterminarEstadoNodo(hijo) != eEstadoCargaNodo_Underflow)
		{
			this->Escribir(_nroNodoPadre, _padre);
			this->Escribir(nroNodoHijo, hijo);
		}
		else if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)	// Observacion: Siempre da verdadero
		{
			this->Escribir(_nroNodoPadre, _padre);
			this->ResolverUnderflow(nroNodoHijo, (iNodoArbolPuntoOptimoNodoInternoPtr) hijo);
		} else // Observacion: Nunca se llega aqui

			ResolverUnderflow(_nroNodoPadre, _padre, nroNodoHijo,
					(iNodoArbolPuntoOptimoNodoHojaPtr) hijo);
	}

	if (hijo)
		hijo->Dispose();
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoPadre, iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo, iNodoArbolPuntoOptimoNodoHojaPtr _hijo)
{
	size_t nroNodoHermano = 0;
	size_t* pNroNodoHermano = &nroNodoHermano;
	iNodoArbolPuntoOptimoPtr pHermano = NULL;
	iNodoArbolPuntoOptimoPtr* ppHermano = &pHermano;

	if ((this->archivo->DeterminarPorcentajeCarga(_padre) + this->archivo->DeterminarPorcentajeCarga(_hijo)) <= 100)
	{
		iNodoArbolPuntoOptimoPtr padreNuevo = this->Fusionar(_padre, _nroNodoHijo, _hijo);
		this->archivo->LiberarNodo(_nroNodoHijo);
		this->Escribir(_nroNodoPadre, padreNuevo);

		padreNuevo->Dispose();
	}
	else if (ObtenerHermano(_padre, _nroNodoHijo, pNroNodoHermano, ppHermano)
			== eHermanoVpTree_ABM__NodoInterno) {

		Escribir(_nroNodoPadre, (*ppHermano));
		archivo->LiberarNodo(_nroNodoHijo);
		archivo->LiberarNodo(nroNodoHermano);

		while (_padre->ObtenerCantidadRegistros())
			Alta(_padre->QuitarRegistro(), false);

		while (_hijo->ObtenerCantidadRegistros())
			Alta(_hijo->QuitarRegistro(), false);
	}
	else
	{
		iNodoArbolPuntoOptimoPtr padreNuevo = Fusionar(_padre, _nroNodoHijo, _hijo);
		archivo->LiberarNodo(_nroNodoHijo);

		if (nroNodoHermano)
		{
			iNodoArbolPuntoOptimoPtr padreNuevo2 = this->Fusionar((iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo, nroNodoHermano, (iNodoArbolPuntoOptimoNodoHojaPtr) (*ppHermano));
			this->archivo->LiberarNodo(nroNodoHermano);

			padreNuevo->Dispose();
			padreNuevo = padreNuevo2;
		}
		if (archivo->DeterminarEstadoNodo(padreNuevo) == eEstadoCargaNodo_Overflow)
			ResolverOverflow(_nroNodoPadre, (iNodoArbolPuntoOptimoNodoHojaPtr) padreNuevo);
		else
			Escribir(_nroNodoPadre, padreNuevo);

		padreNuevo->Dispose();
	}

	if ((*ppHermano))
		(*ppHermano)->Dispose();
}

// Reparte los contenidos de un nodo entre 2 y devuelve el radio
float VpTree_ABM::Repartir(iNodoArbolPuntoOptimoPtr padre, iFeaturePtr pivote, iNodoArbolPuntoOptimoPtr hijo1, iNodoArbolPuntoOptimoPtr hijo2)
{
	iHeapPtr heapMinimos = HeapFactory_Nuevo(eHeap::eHeap_Minimo);

	size_t cantidadRegistros = padre->ObtenerCantidadRegistros();

	for (size_t i = 0; i < cantidadRegistros; i++)
	{
		sHeapComponentPtr heapComponent = new sHeapComponent();
		iRegistroPtr registro = padre->ObtenerRegistro(i);
		heapComponent->valor = this->Distancia(pivote,
				registro->GetFeature(this->nroCampoClave));
		heapComponent->object = registro;

		heapMinimos->Push(heapComponent);
	}

	for (size_t i = 0; i < cantidadRegistros / 2; i++)
	{
		sHeapComponentPtr component = heapMinimos->Pop();
		hijo1->AgregarRegistro((iRegistroPtr)component->object);
		delete component;
	}

	float radio = heapMinimos->Peek()->valor;
	for (size_t i = cantidadRegistros / 2; i < cantidadRegistros; i++)
	{
		sHeapComponentPtr component = heapMinimos->Pop();
		hijo2->AgregarRegistro((iRegistroPtr)component->object);
		delete component;
	}

	delete heapMinimos;

	return radio;
}

void VpTree_ABM::ResolverOverflow(size_t _nroNodoHijo,
		iNodoArbolPuntoOptimoNodoHojaPtr _hijo)
{
	iFeaturePtr pivote = this->GenerarPivote(_hijo);
	iNodoArbolPuntoOptimoPtr hijos[2] = {NULL, NULL};

	size_t hijoIzquierdo = this->archivo->NuevoNodo((iNodoPtr *)hijos, eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja);
	size_t hijoDerecho = this->archivo->NuevoNodo((iNodoPtr *)(hijos + 1), eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja);

	float radio = this->Repartir(_hijo, pivote, hijos[0], hijos[1]);

	iNodoArbolPuntoOptimoNodoInternoPtr padre = (iNodoArbolPuntoOptimoNodoInternoPtr)NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno);

	eEstadoCargaNodo estadoPadre = this->archivo->DeterminarEstadoNodo(padre);
	eEstadoCargaNodo estadoHijos[2] = {this->archivo->DeterminarEstadoNodo(hijos[0]), this->archivo->DeterminarEstadoNodo(hijos[1])};
	char hijoActual = 0;

	while ((estadoHijos[hijoActual] != eEstadoCargaNodo::eEstadoCargaNodo_Underflow) &&
			(estadoPadre != eEstadoCargaNodo::eEstadoCargaNodo_Overflow))
	{
		iRegistroPtr registro = hijos[hijoActual]->QuitarRegistro();
		eEstadoCargaNodo nuevoEstadoHijo = this->archivo->DeterminarEstadoNodo(hijos[hijoActual]);
		if (nuevoEstadoHijo == eEstadoCargaNodo::eEstadoCargaNodo_Underflow)
		{
			hijos[hijoActual]->AgregarRegistro(registro);
			break;	// se rompio el ciclo
		}

		padre->AgregarRegistro(registro);
		eEstadoCargaNodo nuevoEstadoPadre = this->archivo->DeterminarEstadoNodo(padre);
		if (nuevoEstadoPadre == eEstadoCargaNodo::eEstadoCargaNodo_Overflow)
		{
			padre->QuitarRegistro(padre->ObtenerCantidadRegistros() - 1);
			hijos[hijoActual]->AgregarRegistro(registro);
			break;	// se rompio el ciclo
		}

		estadoPadre = nuevoEstadoPadre;
		estadoHijos[hijoActual] = nuevoEstadoHijo;
		hijoActual = 1 - hijoActual;
	}

	if (estadoPadre == eEstadoCargaNodo::eEstadoCargaNodo_Underflow)
	{
		size_t cantidadRegistros = hijos[1]->ObtenerCantidadRegistros();
		for (size_t i = cantidadRegistros; i > 0; i--)
			padre->AgregarRegistro(hijos[1]->QuitarRegistro(i - 1));

		padre->EstablecerHijoDerecho(0);
	}
	else
	{
		this->archivo->EscribirNodo(hijoDerecho, hijos[1]);
		padre->EstablecerHijoDerecho(hijoDerecho);
	}

	hijos[1]->Dispose();
	this->archivo->EscribirNodo(hijoIzquierdo, hijos[0]);
	hijos[0]->Dispose();

	padre->EstablecerPivote(pivote);
	pivote->Dispose();

	padre->EstablecerRadio(radio);
	padre->EstablecerHijoIzquierdo(hijoIzquierdo);
	
	this->Escribir(_nroNodoHijo, padre);
	
	padre->Dispose();
}

iNodoArbolPuntoOptimoPtr VpTree_ABM::Fusionar(iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo, iNodoArbolPuntoOptimoNodoHojaPtr _hijo)
{
	if (_nroNodoHijo == 0)
		Throw(ExceptionType_InvalidArg, "La raiz no puede ser hija del padre.");

	iNodoArbolPuntoOptimoPtr padreNuevo = NULL;

	if (_padre->ObtenerHijoDerecho() == _nroNodoHijo)
		_padre->EstablecerHijoDerecho(0);
	else if (_padre->ObtenerHijoIzquierdo() == _nroNodoHijo)
		_padre->EstablecerHijoIzquierdo(0);
	else
		Throw(ExceptionType_InvalidArg, "El nodo provisto no es un hijo del nodo padre");

	if (_padre->ObtenerHijoDerecho() == _padre->ObtenerHijoIzquierdo())
		padreNuevo = NodoArbolPuntoOptimoFactory_Nuevo(
				eNodoArbolPuntoOptimo_Hoja);
	else {

		padreNuevo = NodoArbolPuntoOptimoFactory_Nuevo(
				eNodoArbolPuntoOptimo_Interno);

		((iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo)->EstablecerPivote(
				_padre->ObtenerPivote()->Clone());
		((iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo)->EstablecerRadio(
				_padre->ObtenerRadio());
		((iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo)->EstablecerHijoDerecho(
				_padre->ObtenerHijoDerecho());
		((iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo)->EstablecerHijoIzquierdo(
				_padre->ObtenerHijoIzquierdo());
	}

	while (_padre->ObtenerCantidadRegistros())
		padreNuevo->AgregarRegistro(_padre->QuitarRegistro());

	while (_hijo->ObtenerCantidadRegistros())
		padreNuevo->AgregarRegistro(_hijo->QuitarRegistro());

	return padreNuevo;
}

eHermanoVpTree_ABM VpTree_ABM::ObtenerHermano(
		iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
		size_t* _nroNodoHermano, iNodoArbolPuntoOptimoPtr* _hermano) {

	if (_nroNodoHijo == 0)
		Throw(" ", "La raiz no puede ser hija del padre.");

	if (_padre->ObtenerHijoDerecho() == _nroNodoHijo)
		*_nroNodoHermano = _padre->ObtenerHijoIzquierdo();
	else
		*_nroNodoHermano = _padre->ObtenerHijoDerecho();

	if (*_nroNodoHermano == 0) {

		*_hermano = NULL;
		return eHermanoVpTree_ABM__Inexistente;
	}

	*_hermano = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(*_nroNodoHermano);

	if ((*_hermano)->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja)
		return eHermanoVpTree_ABM__Hoja;
	else
		return eHermanoVpTree_ABM__NodoInterno;
}

iFeaturePtr VpTree_ABM::GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr _hoja) 
{
	size_t cantidad = _hoja->ObtenerCantidadRegistros();
	if (!cantidad)
		return NULL;

	iFeaturePtr pivote = NULL;

	iFeaturePtr clave = _hoja->ObtenerRegistro(0)->GetFeature(this->nroCampoClave);
	if (clave->ObtenerTipo() & Mascara_Numero)
	{
		size_t listaClaves[cantidad];

		for (size_t i = 0; i < cantidad; i++)
			listaClaves[i] = _hoja->ObtenerRegistro(i)->GetFeature(0)->AsNumber().entero.enteroSinSigno.entero32SinSigno;

		uValue number;
		number.primitivo.numero.entero.enteroSinSigno.entero32SinSigno = this->espacioMetrico->CalcularPivote(listaClaves, cantidad);
		pivote = FeatureFactory_Nuevo(number, eValueType::eValueType_U4);
	}
	else
	{
		sCadenaANSI *listaClaves[cantidad];

		for (size_t i = 0; i < cantidad; i++)
			listaClaves[i] = _hoja->ObtenerRegistro(i)->GetFeature(0)->AsCadenaANSI();

		sCadenaANSI *cadena = this->espacioMetrico->CalcularPivote(listaClaves, cantidad);
		pivote = FeatureFactory_Nuevo(cadena);
		if (cadena->cadena)
			delete[] cadena->cadena;
		delete cadena;
	}

	return pivote;
}

float VpTree_ABM::CalcularRadio(iFeaturePtr _pivote,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja)
{

	iHeapPtr heapMinimos = HeapFactory_Nuevo(eHeap::eHeap_Minimo);

	size_t cantidadRegistros = _hoja->ObtenerCantidadRegistros();

	// insertamos en orden todos los registros, luego quitamos la mitad
	// y nos quedamos con el radio igual a la distancia del siguiente en el heap

	for (size_t i = 0; i < cantidadRegistros; i++)
	{
		sHeapComponentPtr heapComponent = new sHeapComponent();
		iRegistroPtr registro = _hoja->ObtenerRegistro(i);
		heapComponent->valor = this->Distancia(_pivote, registro->GetFeature(this->nroCampoClave));
		heapComponent->object = registro;

		heapMinimos->Push(heapComponent);
	}

	for (size_t i = 0; i < cantidadRegistros / 2; i++)
		delete heapMinimos->Pop();

	float radio = heapMinimos->Peek()->valor;
	delete heapMinimos;	// borra el resto

	return radio;
}

eResultadoVpTree_ABM VpTree_ABM::Alta(iRegistroPtr _reg, size_t _nroNodoPadre, iNodoArbolPuntoOptimoPtr _padre)
{
	Sistema_Execute(_padre->AgregarRegistro(_reg->Copiar()););

	if (archivo->DeterminarEstadoNodo(_padre) != eEstadoCargaNodo_Overflow)
	{
		Sistema_Execute(this->Escribir(_nroNodoPadre, _padre););
		return eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok;
	}

	if (_padre->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja)
		Sistema_Execute(this->ResolverOverflow(_nroNodoPadre, (iNodoArbolPuntoOptimoNodoHojaPtr) _padre););
	else
	{
		iFeaturePtr key;
		iFeaturePtr pivote;
		size_t nroNodoHijo;
		iNodoPtr hijo;

		_padre->QuitarRegistro(_padre->ObtenerCantidadRegistros() - 1);
		Sistema_Execute(pivote = ((iNodoArbolPuntoOptimoNodoInternoPtr) _padre)->ObtenerPivote(););
		Sistema_Execute(key = _reg->GetFeature(this->nroCampoClave););

		if (Distancia(key, pivote) < ((iNodoArbolPuntoOptimoNodoInternoPtr) _padre)->ObtenerRadio())
			nroNodoHijo = ((iNodoArbolPuntoOptimoNodoInternoPtr) _padre)->ObtenerHijoIzquierdo();
		else
			nroNodoHijo = ((iNodoArbolPuntoOptimoNodoInternoPtr) _padre)->ObtenerHijoDerecho();

		if (!nroNodoHijo)
		{
			nroNodoHijo = this->archivo->NuevoNodo(&hijo, eNodoArbolPuntoOptimo_Hoja);
			this->ResolverUnderflow(_nroNodoPadre, (iNodoArbolPuntoOptimoNodoInternoPtr) _padre, nroNodoHijo, (iNodoArbolPuntoOptimoNodoHojaPtr) hijo);
		}
		else
		{
			hijo = archivo->LeerNodo(nroNodoHijo);
			Sistema_Execute(Alta(_reg, nroNodoHijo, (iNodoArbolPuntoOptimoPtr) hijo););
		}

		hijo->Dispose();
	}

	return eResultadoVpTree_ABM__Ok;
}

eResultadoVpTree_ABM VpTree_ABM::Alta(iRegistroPtr _reg, bool _unicidad)
{
	if (_unicidad)
		if (Buscar(_reg->GetFeature(this->nroCampoClave), NULL) == eResultadoVpTree_ABM__Ok)
			return eResultadoVpTree_ABM__Duplicado;

	return Alta(_reg, 0, this->raiz);
}

size_t VpTree_ABM::Ubicar(iFeaturePtr clave, iNodoArbolPuntoOptimoPtr _nodo)
{
	float dist;
	iFeaturePtr key;
	iRegistroPtr reg;

	for (size_t i = 0; i < _nodo->ObtenerCantidadRegistros(); i++)
	{
		reg = _nodo->ObtenerRegistro(i);
		key = reg->GetFeature(nroCampoClave);
		dist = Distancia(key, clave);

		if (!dist)
			return i;
	}

	return _nodo->ObtenerCantidadRegistros() + 1;
}

eResultadoVpTree_ABM VpTree_ABM::Baja(iFeaturePtr _key, size_t _nroNodoPadre, iNodoArbolPuntoOptimoPtr _padre, size_t _nroNodoHijo, iNodoArbolPuntoOptimoPtr _hijo)
{
	size_t posicionRegistro = Ubicar(_key, _hijo);

	if (posicionRegistro >= _hijo->ObtenerCantidadRegistros())
	{
		if (_hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja)
			return eResultadoVpTree_ABM__Inexistente;

		iFeaturePtr pivote;
		size_t nroNodoNieto;

		pivote = ((iNodoArbolPuntoOptimoNodoInternoPtr) _hijo)->ObtenerPivote();

		if (Distancia(_key, pivote) < ((iNodoArbolPuntoOptimoNodoInternoPtr) _hijo)->ObtenerRadio())
			nroNodoNieto = ((iNodoArbolPuntoOptimoNodoInternoPtr) _hijo)->ObtenerHijoIzquierdo();
		else
			nroNodoNieto = ((iNodoArbolPuntoOptimoNodoInternoPtr) _hijo)->ObtenerHijoDerecho();

		if (!nroNodoNieto)
			return eResultadoVpTree_ABM__Inexistente;

		iNodoArbolPuntoOptimoPtr nieto = (iNodoArbolPuntoOptimoPtr) this->archivo->LeerNodo(nroNodoNieto);
		eResultadoVpTree_ABM res = Baja(_key, _nroNodoHijo, _hijo, nroNodoNieto, nieto);
		nieto->Dispose();

		return res;
	}

	(_hijo->QuitarRegistro(posicionRegistro))->Dispose();

	if ((archivo->DeterminarEstadoNodo(_hijo) == eEstadoCargaNodo_Underflow) && (_hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Interno))
		this->ResolverUnderflow(_nroNodoHijo,
				(iNodoArbolPuntoOptimoNodoInternoPtr) _hijo);

	else if ((archivo->DeterminarEstadoNodo(_hijo) == eEstadoCargaNodo_Underflow) && (_hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja) && _nroNodoHijo)
		this->ResolverUnderflow(_nroNodoPadre, (iNodoArbolPuntoOptimoNodoInternoPtr) _padre, _nroNodoHijo, (iNodoArbolPuntoOptimoNodoHojaPtr) _hijo);
	else
		this->Escribir(_nroNodoHijo, _hijo);

	return eResultadoVpTree_ABM__Ok;
}

eResultadoVpTree_ABM VpTree_ABM::Baja(const iFeaturePtr _key)
{
	iNodoArbolPuntoOptimoPtr copiaRaiz = raiz->Clone();

	eResultadoVpTree_ABM res = Baja(_key, 0, NULL, 0, copiaRaiz);

	copiaRaiz->Dispose();
	return res;
}

eResultadoVpTree_ABM VpTree_ABM::Modificacion(const iRegistroPtr _reg)
{
	iFeaturePtr key = _reg->GetFeature(nroCampoClave);

	if (this->Baja(key) == eResultadoVpTree_ABM__Inexistente)
		return  eResultadoVpTree_ABM__Inexistente;

	return this->Alta(_reg, false);
}

eResultadoVpTree_ABM VpTree_ABM::Buscar(const iFeaturePtr _key, iRegistroPtr *_reg)
{
	iRegistroPtr registro = NULL;

	iNodoArbolPuntoOptimoPtr nodoActual = this->raiz;

	while (true)
	{
		size_t posicionRegistro = this->Ubicar(_key, nodoActual);
		if (posicionRegistro < nodoActual->ObtenerCantidadRegistros())
		{
			registro = nodoActual->ObtenerRegistro(posicionRegistro)->Copiar();
			break;
		}

		if (nodoActual->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja)
			return eResultadoVpTree_ABM::eResultadoVpTree_ABM__Inexistente;

		iNodoArbolPuntoOptimoNodoInternoPtr interno = (iNodoArbolPuntoOptimoNodoInternoPtr)nodoActual;
		float distanciaAPivote = this->Distancia(_key, interno->ObtenerPivote());
		size_t nodoALeer = 0;
		if (distanciaAPivote < interno->ObtenerRadio())
			nodoALeer = interno->ObtenerHijoIzquierdo();
		else
			nodoALeer = interno->ObtenerHijoDerecho();

		if (!nodoALeer)
			break;

		if (nodoActual && nodoActual != this->raiz)
			nodoActual->Dispose();

		nodoActual = (iNodoArbolPuntoOptimoPtr)this->archivo->LeerNodo(nodoALeer);

		// por las dudas
		if (!nodoActual)
			break;
	}
	if (nodoActual && nodoActual != this->raiz)
		nodoActual->Dispose();

	if (_reg)
		*_reg = registro;

	if (!registro)
		return eResultadoVpTree_ABM::eResultadoVpTree_ABM__Inexistente;

	return eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok;
}
