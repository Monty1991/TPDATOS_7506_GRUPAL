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
#include "../../../Utils/StringUtils/Headers/StringUtils.h"
#include <string.h>

VpTree_ABM::VpTree_ABM(const char *archivo, size_t nroCampoClave, size_t tamanioNodo, size_t cargaMinima, size_t tolerancia): nroCampoClave(nroCampoClave)
{
	this->espacioMetrico = EspacioMetricoFactory_Nuevo();

	this->archivo = ArchivoArbolFactory_Nuevo(archivo, tamanioNodo, cargaMinima, tolerancia, eTipoArbol::eTipoArbol_ArbolPuntoOptimo);

	this->raiz = (iNodoArbolPuntoOptimoPtr) this->archivo->LeerNodo(0);

	if (this->raiz == NULL)
	{
		this->raiz = NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja);
		this->Escribir(0, raiz);
	}
}

VpTree_ABM::~VpTree_ABM()
{
	if (this->raiz)
		this->raiz->Dispose();

	if (this->archivo)
		this->archivo->Close();

	if (this->espacioMetrico)
		this->espacioMetrico->Dispose();
}

eResultadoABM VpTree_ABM::Alta(iRegistroPtr registro, bool comprobarUnicidad)
{
	if (comprobarUnicidad)
	{
		eResultadoABM resultado;

		Sistema_Execute(resultado = this->Buscar(registro->GetFeature(this->nroCampoClave), NULL););

		if (resultado == eResultadoABM_NoErr)
			return eResultadoABM::eResultadoABM_ClaveDuplicada;
	}

	return this->Alta(registro, 0, this->raiz);
}

eResultadoABM VpTree_ABM::Baja(const iFeaturePtr clave)
{
	eResultadoABM resultado;

	Sistema_Execute(resultado = Baja(clave, 0, NULL, 0, this->raiz););

	return resultado;
}

eResultadoABM VpTree_ABM::Modificacion(const iRegistroPtr registro)
{
	iFeaturePtr clave = NULL;
	Sistema_Execute(clave = registro->GetFeature(nroCampoClave););

	eResultadoABM resultado;

	Sistema_Execute(resultado = this->Baja(clave););
	if (resultado != eResultadoABM::eResultadoABM_ClaveNoEncontrada)
		return this->Alta(registro, false);

	return eResultadoABM::eResultadoABM_ClaveNoEncontrada;
}

eResultadoABM VpTree_ABM::Buscar(const iFeaturePtr clave, iRegistroPtr *registro)
{
	eResultadoABM resultado;

	Sistema_Execute(resultado = this->Buscar(clave, registro, this->raiz););

	return resultado;
}

void VpTree_ABM::Dispose()
{
	delete this;
}

/****************************
	Persistencia a disco
****************************/
void VpTree_ABM::Escribir(size_t nroNodo, iNodoArbolPuntoOptimoPtr nodo)
{
	if (!nroNodo && (nodo != this->raiz))
	{
		iNodoPtr viejaRaiz = this->raiz;
		this->raiz = nodo->Copiar();
		viejaRaiz->Dispose();
	}

	this->archivo->EscribirNodo(nroNodo, nodo);
}

/******************************
	Metodos ABM recursivos
******************************/

eResultadoABM VpTree_ABM::Alta(iRegistroPtr registro, size_t nroNodo, iNodoArbolPuntoOptimoPtr nodo)
{
	Sistema_Execute(nodo->AgregarRegistro(registro););

	if (this->archivo->DeterminarEstadoNodo(nodo) != eEstadoCargaNodo::eEstadoCargaNodo_Overflow)
	{
		Sistema_Execute(this->Escribir(nroNodo, nodo););
		return eResultadoABM::eResultadoABM_NoErr;
	}

	if (nodo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja)
		Sistema_Execute(this->ResolverOverflow(nroNodo, (iNodoArbolPuntoOptimoNodoHojaPtr) nodo););
	else
	{
		iNodoArbolPuntoOptimoNodoInternoPtr interno = (iNodoArbolPuntoOptimoNodoInternoPtr) nodo;

		iFeaturePtr clave = NULL;
		iFeaturePtr pivote = NULL;
		size_t nroNodoHijo = 0;
		iNodoPtr hijo = NULL;

		interno->QuitarRegistro(nodo->ObtenerCantidadRegistros() - 1);
		Sistema_Execute(pivote = interno->ObtenerPivote(););
		Sistema_Execute(clave = registro->GetFeature(this->nroCampoClave););

		if (Distancia(clave, pivote) < interno->ObtenerRadio())
			nroNodoHijo = interno->ObtenerHijoIzquierdo();
		else
			nroNodoHijo = interno->ObtenerHijoDerecho();

		if (!nroNodoHijo)
		{
			nroNodoHijo = this->archivo->NuevoNodo(0, &hijo, eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja);
			AgregarHijo(interno, nroNodoHijo);
			hijo->AgregarRegistro(registro);
			this->ResolverUnderflow(nroNodo, interno, nroNodoHijo, (iNodoArbolPuntoOptimoNodoHojaPtr) hijo);
		}
		else
		{
			hijo = archivo->LeerNodo(nroNodoHijo);
			Sistema_Execute(Alta(registro, nroNodoHijo, (iNodoArbolPuntoOptimoPtr) hijo););
		}

		hijo->Dispose();
	}

	return eResultadoABM::eResultadoABM_NoErr;
}

eResultadoABM VpTree_ABM::Baja(iFeaturePtr clave, size_t nroNodo, iNodoArbolPuntoOptimoPtr nodo, size_t nroNodoHijo, iNodoArbolPuntoOptimoPtr hijo)
{
	size_t posicionRegistro = 0;
	Sistema_Execute(posicionRegistro = this->UbicarRegistro(clave, hijo););

	if (posicionRegistro >= hijo->ObtenerCantidadRegistros())
	{
		if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja)
			return eResultadoABM_ClaveNoEncontrada;

		iFeaturePtr pivote = NULL;
		size_t nroNodoNieto = 0;
		iNodoArbolPuntoOptimoNodoInternoPtr interno = (iNodoArbolPuntoOptimoNodoInternoPtr) hijo;

		pivote = interno->ObtenerPivote();

		if (Distancia(clave, pivote) < interno->ObtenerRadio())
			nroNodoNieto = interno->ObtenerHijoIzquierdo();
		else
			nroNodoNieto = interno->ObtenerHijoDerecho();

		if (!nroNodoNieto)
			return eResultadoABM_ClaveNoEncontrada;

		iNodoArbolPuntoOptimoPtr nieto = (iNodoArbolPuntoOptimoPtr) this->archivo->LeerNodo(nroNodoNieto);

		eResultadoABM resultado;

		Sistema_Execute(resultado = this->Baja(clave, nroNodoHijo, hijo, nroNodoNieto, nieto););

		nieto->Dispose();

		return resultado;
	}

	iRegistroPtr registro = NULL;
	Sistema_Execute(registro = hijo->QuitarRegistro(posicionRegistro););
	if (!registro)
		Throw("Unexpected result", "Registro encontrado == NULL ?!")

	registro->Dispose();

	if (this->archivo->DeterminarEstadoNodo(hijo) == eEstadoCargaNodo::eEstadoCargaNodo_Underflow)
	{
		if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)
			Sistema_Execute(this->ResolverUnderflow(nroNodoHijo, (iNodoArbolPuntoOptimoNodoInternoPtr) hijo););
		else if (nroNodoHijo)
			Sistema_Execute(this->ResolverUnderflow(nroNodo, (iNodoArbolPuntoOptimoNodoInternoPtr) nodo, nroNodoHijo, (iNodoArbolPuntoOptimoNodoHojaPtr) hijo););
		else
			Sistema_Execute(this->Escribir(nroNodoHijo, hijo););
	}
	else
		Sistema_Execute(this->Escribir(nroNodoHijo, hijo););

	return eResultadoABM_NoErr;
}

eResultadoABM VpTree_ABM::Buscar(const iFeaturePtr clave, iRegistroPtr *registro, iNodoArbolPuntoOptimoPtr nodo)
{
	if (!nodo)
		return eResultadoABM::eResultadoABM_ClaveNoEncontrada;

	size_t posicionRegistro = 0;
	Sistema_Execute(posicionRegistro = this->UbicarRegistro(clave, nodo););
	if (posicionRegistro < nodo->ObtenerCantidadRegistros())
	{
		if (registro)
			*registro = nodo->ObtenerRegistro(posicionRegistro)->Copiar();

		return eResultadoABM::eResultadoABM_NoErr;
	}

	if (nodo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja)
		return eResultadoABM::eResultadoABM_ClaveNoEncontrada;

	iNodoArbolPuntoOptimoNodoInternoPtr interno = (iNodoArbolPuntoOptimoNodoInternoPtr) nodo;
	double distanciaAPivote = 0;

	Sistema_Execute(distanciaAPivote = this->Distancia(clave, interno->ObtenerPivote()););

	size_t nodoALeer = 0;
	if (distanciaAPivote < interno->ObtenerRadio())
		nodoALeer = interno->ObtenerHijoIzquierdo();
	else
		nodoALeer = interno->ObtenerHijoDerecho();

	if (!nodoALeer)
		return eResultadoABM::eResultadoABM_ClaveNoEncontrada;

	eResultadoABM resultado = eResultadoABM::eResultadoABM_ClaveNoEncontrada;

	iNodoArbolPuntoOptimoPtr nodoHijo = NULL;
	Sistema_Execute(nodoHijo = (iNodoArbolPuntoOptimoPtr) this->archivo->LeerNodo(nodoALeer););

	if (nodoHijo)
	{
		Sistema_Execute(resultado = this->Buscar(clave, registro, nodoHijo););
		nodoHijo->Dispose();
	}

	return resultado;
}

/**************************
	De Espacio Metrico
**************************/

double VpTree_ABM::Distancia(iFeaturePtr clave1, iFeaturePtr clave2)
{
	if (!clave1)
		Throw(ExceptionType_InvalidArg, "clave1 == NULL");

	if (!clave2)
		Throw(ExceptionType_InvalidArg, "clave2 == NULL");

	if (clave1->ObtenerTipo() != clave2->ObtenerTipo())
		Throw(ExceptionType_InvalidArg, "clave1->Tipo != clave2->Tipo");

	// numerico -> usar claves numericas
	if (clave1->ObtenerTipo() & Mascara_Numero)
		return this->espacioMetrico->CalcularDistancia(clave1->AsNumber().entero.enteroSinSigno.entero32SinSigno, clave2->AsNumber().entero.enteroSinSigno.entero32SinSigno);

	// no numerico -> usar claves de cadenas
	if (!(clave1->ObtenerTipo() & Mascara_Numero))
		return this->espacioMetrico->CalcularDistancia(clave1->AsCadenaANSI(), clave2->AsCadenaANSI());

	Throw(ExceptionType_InvalidArg, "clave1->Tipo not supported");
}

iFeaturePtr VpTree_ABM::GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr nodo) 
{
	size_t cantidad = nodo->ObtenerCantidadRegistros();
	if (!cantidad)
		return NULL;

	iRegistroPtr registro = NULL;
	iFeaturePtr pivote = NULL;

	Sistema_Execute(registro = nodo->ObtenerRegistro(0););

	iFeaturePtr clave = NULL;
	Sistema_Execute(clave = registro->GetFeature(this->nroCampoClave););

	if (clave->ObtenerTipo() & Mascara_Numero)
	{
		size_t listaClaves[cantidad];

		for (size_t i = 0; i < cantidad; i++)
		{
			iRegistroPtr registro = NULL;
			Sistema_Execute(registro = nodo->ObtenerRegistro(i););

			iFeaturePtr clave = NULL;
			Sistema_Execute(clave = registro->GetFeature(this->nroCampoClave););

			listaClaves[i] = clave->AsNumber().entero.enteroSinSigno.entero32SinSigno;
		}

		uValue number;
		number.primitivo.numero.entero.enteroSinSigno.entero32SinSigno = this->espacioMetrico->CalcularPivote(listaClaves, cantidad);
		pivote = FeatureFactory_Nuevo(number, eValueType::eValueType_U4);
	}
	else
	{
		sCadenaANSI *listaClaves[cantidad];

		for (size_t i = 0; i < cantidad; i++)
		{
			iRegistroPtr registro = NULL;
			Sistema_Execute(registro = nodo->ObtenerRegistro(i););

			iFeaturePtr clave = NULL;
			Sistema_Execute(clave = registro->GetFeature(this->nroCampoClave););

			listaClaves[i] = clave->AsCadenaANSI();
		}

		sCadenaANSI *cadena = this->espacioMetrico->CalcularPivote(listaClaves, cantidad);
		pivote = FeatureFactory_Nuevo(cadena);

		if (cadena->cadena)
			delete[] cadena->cadena;

		delete cadena;
	}

	return pivote;
}

double VpTree_ABM::CalcularRadio(iFeaturePtr pivote, iNodoArbolPuntoOptimoNodoHojaPtr nodo)
{
	iHeapPtr heapMinimos = HeapFactory_Nuevo(eHeap::eHeap_Minimo);

	size_t cantidadRegistros = nodo->ObtenerCantidadRegistros();

	// insertamos en orden todos los registros, luego quitamos la mitad
	// y nos quedamos con el radio igual a la distancia del siguiente en el heap

	for (size_t i = 0; i < cantidadRegistros; i++)
	{
		sHeapComponentPtr heapComponent = new sHeapComponent();

		iRegistroPtr registro = NULL;
		Sistema_Execute(registro = nodo->ObtenerRegistro(i););

		heapComponent->object = registro;

		iFeaturePtr clave = NULL;
		Sistema_Execute(clave = registro->GetFeature(this->nroCampoClave););

		Sistema_Execute(heapComponent->valor = this->Distancia(pivote, clave););

		heapMinimos->Push(heapComponent);
	}

	for (size_t i = 0; i < cantidadRegistros / 2; i++)
		delete heapMinimos->Pop();

	double radio = heapMinimos->Peek()->valor;
	heapMinimos->Dispose();	// borra el resto

	return radio;
}

double VpTree_ABM::Partir(iNodoArbolPuntoOptimoPtr nodo, iFeaturePtr pivote, iNodoArbolPuntoOptimoPtr hijo1, iNodoArbolPuntoOptimoPtr hijo2)
{
	iHeapPtr heapMinimos = HeapFactory_Nuevo(eHeap::eHeap_Minimo);

	size_t cantidadRegistros = nodo->ObtenerCantidadRegistros();

	for (size_t i = 0; i < cantidadRegistros; i++)
	{
		sHeapComponentPtr heapComponent = new sHeapComponent();

		iRegistroPtr registro = NULL;
		Sistema_Execute(registro = nodo->ObtenerRegistro(i););

		heapComponent->object = registro->Copiar();

		iFeaturePtr clave = NULL;
		Sistema_Execute(clave = registro->GetFeature(this->nroCampoClave););

		Sistema_Execute(heapComponent->valor = this->Distancia(pivote, clave););

		heapMinimos->Push(heapComponent);
	}

	for (size_t i = 0; i < cantidadRegistros / 2; i++)
	{
		sHeapComponentPtr component = heapMinimos->Pop();
		hijo1->AgregarRegistro((iRegistroPtr) component->object);
		delete component;
	}

	double radio = heapMinimos->Peek()->valor;
	for (size_t i = cantidadRegistros / 2; i < cantidadRegistros; i++)
	{
		sHeapComponentPtr component = heapMinimos->Pop();
		hijo2->AgregarRegistro((iRegistroPtr) component->object);
		delete component;
	}

	heapMinimos->Dispose();

	return radio;
}

/**************************
	Auxiliares de nodo
**************************/
bool VpTree_ABM::CompararClaves(iFeaturePtr clave1, iFeaturePtr clave2)
{
	if (clave1 == clave2)
		return true;

	if (clave1->ObtenerTipo() != clave2->ObtenerTipo())
		Throw(ExceptionType_InvalidArg, "clave1->Tipo != clave2->Tipo");

	if (clave1->ObtenerTipo() & Mascara_Numero)
	{
		size_t valorClave1 = clave1->AsNumber().entero.enteroSinSigno.entero32SinSigno;
		size_t valorClave2 = clave2->AsNumber().entero.enteroSinSigno.entero32SinSigno;

		return (valorClave1 == valorClave2);
	}
	else
	{
		if (clave1->AsCadenaANSI()->largo != clave2->AsCadenaANSI()->largo)
			return false;

		return !memcmp(clave1->AsCadenaANSI()->cadena, clave2->AsCadenaANSI()->cadena, clave1->AsCadenaANSI()->largo);
	}

	Throw("Unexpected Error", "Ehm, shouldn't get here");
}

size_t VpTree_ABM::UbicarRegistro(iFeaturePtr clave, iNodoArbolPuntoOptimoPtr nodo)
{
	for (size_t i = 0; i < nodo->ObtenerCantidadRegistros(); i++)
	{
		iRegistroPtr registro = NULL;
		Sistema_Execute(registro = nodo->ObtenerRegistro(i););

		iFeaturePtr key = NULL;
		Sistema_Execute(key = registro->GetFeature(this->nroCampoClave););

		bool resultado;
		Sistema_Execute(resultado = this->CompararClaves(key, clave););

		if (resultado)
			return i;
	}

	return nodo->ObtenerCantidadRegistros();
}

eHermanoVpTree_ABM VpTree_ABM::ObtenerHermano(iNodoArbolPuntoOptimoNodoInternoPtr nodoPadre, size_t nroNodoHijo, size_t *nroNodoHermano, iNodoArbolPuntoOptimoPtr *nodoHermano)
{
	if (!nroNodoHijo)
		Throw(ExceptionType_InvalidArg, "La raiz no tiene padre.");

	if (nodoPadre->ObtenerHijoDerecho() == nroNodoHijo)
		*nroNodoHermano = nodoPadre->ObtenerHijoIzquierdo();
	else
		*nroNodoHermano = nodoPadre->ObtenerHijoDerecho();

	if (!*nroNodoHermano)
	{
		*nodoHermano = NULL;
		return eHermanoVpTree_ABM::eHermanoVpTree_ABM_Inexistente;
	}

	*nodoHermano = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(*nroNodoHermano);

	if ((*nodoHermano)->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja)
		return eHermanoVpTree_ABM::eHermanoVpTree_ABM_Hoja;
	else
		return eHermanoVpTree_ABM::eHermanoVpTree_ABM_NodoInterno;
}

void VpTree_ABM::AgregarHijo(iNodoArbolPuntoOptimoNodoInternoPtr nodoPadre, size_t nroNodoHijo)
{
	if (!nroNodoHijo)
		Throw(ExceptionType_InvalidArg, "La raiz no puede ser agregada como hijo.");

	if ((nodoPadre->ObtenerHijoIzquierdo() == nroNodoHijo) || (nodoPadre->ObtenerHijoDerecho() == nroNodoHijo))
		Throw("Unexpected error", "El hijo ya fué agregado con anterioridad.");

	if (!nodoPadre->ObtenerHijoIzquierdo())
		nodoPadre->EstablecerHijoIzquierdo(nroNodoHijo);
	else if (!nodoPadre->ObtenerHijoDerecho())
		nodoPadre->EstablecerHijoDerecho(nroNodoHijo);
	else
		Throw("Unexpected error", "El padre ya cuenta con sus dos hjos.");
}

iNodoArbolPuntoOptimoPtr VpTree_ABM::Fusionar(iNodoArbolPuntoOptimoNodoInternoPtr nodoPadre, size_t nroNodoHijo, iNodoArbolPuntoOptimoNodoHojaPtr nodoHijo)
{
	if (nroNodoHijo == 0)
		Throw(ExceptionType_InvalidArg, "La raiz no puede ser hija del padre.");

	iNodoArbolPuntoOptimoPtr padreNuevo = NULL;

	if (nodoPadre->ObtenerHijoDerecho() == nroNodoHijo)
		nodoPadre->EstablecerHijoDerecho(0);
	else if (nodoPadre->ObtenerHijoIzquierdo() == nroNodoHijo)
		nodoPadre->EstablecerHijoIzquierdo(0);
	else
		Throw(ExceptionType_InvalidArg, "El nodo provisto no es un hijo del nodo padre");

	if (nodoPadre->ObtenerHijoDerecho() == nodoPadre->ObtenerHijoIzquierdo())
		padreNuevo = NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja);
	else
	{
		padreNuevo = NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno);
		iNodoArbolPuntoOptimoNodoInternoPtr interno = (iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo;

		interno->EstablecerPivote(nodoPadre->ObtenerPivote()->Clone());
		interno->EstablecerRadio(nodoPadre->ObtenerRadio());
		interno->EstablecerHijoDerecho(nodoPadre->ObtenerHijoDerecho());
		interno->EstablecerHijoIzquierdo(nodoPadre->ObtenerHijoIzquierdo());
	}

	for (size_t i = 0; i < nodoPadre->ObtenerCantidadRegistros(); i++)
	{
		iRegistroPtr registro = NULL;
		Sistema_Execute(registro = nodoPadre->ObtenerRegistro(i););

		if (registro)
			padreNuevo->AgregarRegistro(registro->Copiar());
	}

	for (size_t i = 0; i < nodoHijo->ObtenerCantidadRegistros(); i++)
	{
		iRegistroPtr registro = NULL;
		Sistema_Execute(registro = nodoHijo->ObtenerRegistro(i););

		if (registro)
			padreNuevo->AgregarRegistro(registro->Copiar());
	}

	return padreNuevo;
}

/********************************************
	Resolucion de overflows y underflows
********************************************/
void VpTree_ABM::ResolverUnderflow(size_t nroNodo, iNodoArbolPuntoOptimoNodoInternoPtr nodo)
{
	size_t nroNodoHijo = nodo->ObtenerHijoDerecho();

	if (!nroNodoHijo)
		if (!(nroNodoHijo = nodo->ObtenerHijoIzquierdo()))
			Throw("Unexpected Error", "Nodo interno sin hijos.");

	iNodoArbolPuntoOptimoPtr hijo = (iNodoArbolPuntoOptimoPtr) this->archivo->LeerNodo(nroNodoHijo);

	while (this->archivo->DeterminarEstadoNodo(nodo) == eEstadoCargaNodo_Underflow)
		nodo->AgregarRegistro(hijo->QuitarRegistro());

	// En este punto, nodo tiene carga minima
	// Si el otro nodo esta bien, terminamos
	if (this->archivo->DeterminarEstadoNodo(hijo) != eEstadoCargaNodo_Underflow)
	{
		this->Escribir(nroNodo, nodo);
		this->Escribir(nroNodoHijo, hijo);
	}
	else if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja)
	{
		// Si es una hoja en underflow, cabe dentro del nodo, por lo que lo traemos al nodo
		iNodoArbolPuntoOptimoPtr padreNuevo = this->Fusionar(nodo, nroNodoHijo, (iNodoArbolPuntoOptimoNodoHojaPtr) hijo);
		this->archivo->LiberarNodo(nroNodoHijo);
		this->Escribir(nroNodo, padreNuevo);

		padreNuevo->Dispose();
	}
	else
	{
		// Solucionado para nodo, queda el hijo (que es interno en underflow, mismo problema -> recursion).
		this->Escribir(nroNodo, nodo);

		this->ResolverUnderflow(nroNodoHijo, (iNodoArbolPuntoOptimoNodoInternoPtr) hijo);
	}

	if (hijo)
		hijo->Dispose();
}

void VpTree_ABM::ResolverUnderflow(size_t nroNodoPadre, iNodoArbolPuntoOptimoNodoInternoPtr padre, size_t nroNodoHijo, iNodoArbolPuntoOptimoNodoHojaPtr hijo)
{
	size_t nroNodoHermano = 0;
	iNodoArbolPuntoOptimoPtr hermano = NULL;

	if ((this->archivo->DeterminarPorcentajeCarga(padre) + this->archivo->DeterminarPorcentajeCarga(hijo)) <= 100)
	{
		iNodoArbolPuntoOptimoPtr padreNuevo = NULL;

		Sistema_Execute(padreNuevo = this->Fusionar(padre, nroNodoHijo, hijo););

		this->archivo->LiberarNodo(nroNodoHijo);
		this->Escribir(nroNodoPadre, padreNuevo);

		padreNuevo->Dispose();
	}
	else if (ObtenerHermano(padre, nroNodoHijo, &nroNodoHermano, &hermano) == eHermanoVpTree_ABM::eHermanoVpTree_ABM_NodoInterno)
	{
		Escribir(nroNodoPadre, hermano);
		this->archivo->LiberarNodo(nroNodoHijo);
		this->archivo->LiberarNodo(nroNodoHermano);

		while (padre->ObtenerCantidadRegistros())
			Alta(padre->QuitarRegistro(), false);

		while (hijo->ObtenerCantidadRegistros())
			Alta(hijo->QuitarRegistro(), false);
	}
	else
	{
		iNodoArbolPuntoOptimoPtr padreNuevo = NULL;
		Sistema_Execute(padreNuevo = this->Fusionar(padre, nroNodoHijo, hijo););

		this->archivo->LiberarNodo(nroNodoHijo);

		if (nroNodoHermano)
		{
			iNodoArbolPuntoOptimoPtr padreNuevo2 = NULL;

			Sistema_Execute(padreNuevo2 = this->Fusionar((iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo, nroNodoHermano, (iNodoArbolPuntoOptimoNodoHojaPtr) hermano););
			this->archivo->LiberarNodo(nroNodoHermano);

			padreNuevo->Dispose();
			padreNuevo = padreNuevo2;
		}

		if (archivo->DeterminarEstadoNodo(padreNuevo) == eEstadoCargaNodo::eEstadoCargaNodo_Overflow)
			ResolverOverflow(nroNodoPadre, (iNodoArbolPuntoOptimoNodoHojaPtr) padreNuevo);
		else
			this->Escribir(nroNodoPadre, padreNuevo);

		padreNuevo->Dispose();
	}

	if (hermano)
		hermano->Dispose();
}


void VpTree_ABM::ResolverOverflow(size_t nroNodo, iNodoArbolPuntoOptimoNodoHojaPtr nodo)
{
	const unsigned IZQ = 0;
	const unsigned DER = 1;

	unsigned hijoActual;
	size_t nrosNodosHijos[2] = { 0, 0 };
	iNodoArbolPuntoOptimoNodoHojaPtr hijos[2] = { NULL, NULL };

	nrosNodosHijos[IZQ] = this->archivo->NuevoNodo(1, (iNodoPtr *) hijos, eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja);
	nrosNodosHijos[DER] = this->archivo->NuevoNodo(nrosNodosHijos[IZQ] + 1, (iNodoPtr *) (hijos + 1), eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Hoja);

	iFeaturePtr pivote = NULL;
	Sistema_Execute(pivote = this->GenerarPivote(nodo););

	double radio = 0;
	Sistema_Execute(radio = this->Partir(nodo, pivote, hijos[IZQ], hijos[DER]););

	iNodoArbolPuntoOptimoNodoInternoPtr padre = NULL;
	padre = (iNodoArbolPuntoOptimoNodoInternoPtr) NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno);

	padre->EstablecerRadio(radio);
	padre->EstablecerPivote(pivote);	// ahora el pivote es reesponsabilidad del nodo
	padre->EstablecerHijoIzquierdo(nrosNodosHijos[IZQ]);
	padre->EstablecerHijoDerecho(nrosNodosHijos[DER]);

	eEstadoCargaNodo estadoPadre = this->archivo->DeterminarEstadoNodo(padre);
	eEstadoCargaNodo estadoHijos[2] = { this->archivo->DeterminarEstadoNodo(hijos[IZQ]), this->archivo->DeterminarEstadoNodo(hijos[DER]) };

	if (estadoHijos[IZQ] != eEstadoCargaNodo::eEstadoCargaNodo_Underflow)
		hijoActual = IZQ;
	else
		hijoActual = DER; //Luego de repartir, a lo sumo un hijo estará en underflow

	while ((estadoHijos[hijoActual] != eEstadoCargaNodo::eEstadoCargaNodo_Underflow) && (estadoPadre != eEstadoCargaNodo::eEstadoCargaNodo_Overflow))
	{
		hijoActual = DER - hijoActual;

		Sistema_Execute(padre->AgregarRegistro(hijos[hijoActual]->QuitarRegistro()););
		estadoPadre = this->archivo->DeterminarEstadoNodo(padre);
		estadoHijos[hijoActual] = this->archivo->DeterminarEstadoNodo(hijos[hijoActual]);
	}

	hijos[hijoActual]->AgregarRegistro(padre->QuitarRegistro(padre->ObtenerCantidadRegistros() - 1));

	this->Escribir(nrosNodosHijos[IZQ], hijos[IZQ]);
	hijos[IZQ]->Dispose();

	this->Escribir(nrosNodosHijos[DER], hijos[DER]);
	hijos[DER]->Dispose();

	estadoPadre = this->archivo->DeterminarEstadoNodo(padre);

	if (estadoPadre == eEstadoCargaNodo::eEstadoCargaNodo_Underflow)
		Sistema_Execute(this->ResolverUnderflow(nroNodo, padre););
	else
		Sistema_Execute(this->Escribir(nroNodo, padre););

	padre->Dispose();
}

