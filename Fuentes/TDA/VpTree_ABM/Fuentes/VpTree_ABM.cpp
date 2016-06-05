/*
 * VpTree_ABM.cpp
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#include "../Headers/VpTree_ABM.h"
#include "../../../io/ArchivoArbol/ArchivoArbolFactory.h"
#include "../../../Utils/NodoArbolPuntoOptimo/NodoArbolPuntoOptimoFactory.h"
#include "../../../Utils/EspacioMetrico/EspacioMetricoFactory.h"
#include "../../../Exceptions/ExceptionFactory.h"

VpTree_ABM::~VpTree_ABM() {

	if (raiz) {

		raiz->Dispose();
		raiz = NULL;
	}

	if (archivo) {

		archivo->Close();
		archivo = NULL;
	}

	if (this->espacioMetrico) {

		this->espacioMetrico->Dispose();
		this->espacioMetrico = NULL;
	}
}

void VpTree_ABM::Dispose() {

	delete this;
}

float VpTree_ABM::Distancia(iFeaturePtr _key1, iFeaturePtr _key2) {

	return 0;
}

VpTree_ABM::VpTree_ABM(const char* _fileName, size_t _nroCampoClave,
		size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia) :
		nroCampoClave(_nroCampoClave) {

	this->espacioMetrico = EspacioMetricoFactory_Nuevo();

	archivo = ArchivoArbolFactory_Nuevo(_fileName, _tamanioNodo, _cargaMinima,
			_tolerancia, eTipoArbol_ArbolPuntoOptimo);

	raiz = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(0);

	if (raiz == NULL) {

		raiz = NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo_Hoja);
		archivo->EscribirNodo(0, raiz);
	}
}

void VpTree_ABM::ResolverEstado(eEstadoVpTree_ABM _estado,
		size_t _nroNodoInterno,
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno, size_t _nroHoja,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

	switch (_estado) {

	case eEstadoVpTree_ABM__HojaEnOverflow:
		ResolverOverflow(_nroHoja, _hoja);
		break;

	case eEstadoVpTree_ABM__HojaEnUnderflow:
		ResolverUnderflow(_nroNodoInterno, _nodoInterno, _nroHoja, _hoja);
		break;

	case eEstadoVpTree_ABM__NodoInternoEnUnderflow:
		ResolverUnderflow(_nroNodoInterno, _nodoInterno);
		break;
	}
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoInterno,
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno) {

	size_t nroHijo;
	iNodoArbolPuntoOptimoPtr hijo = NULL;
	iNodoArbolPuntoOptimoNodoHojaPtr hojaNueva = NULL;

	if ((nroHijo = _nodoInterno->ObtenerHijoDerecho()) == 0)
		if ((nroHijo = _nodoInterno->ObtenerHijoIzquierdo()) == 0)
			Throw(" ", "Nodo interno sin hijos.");

	hijo = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(nroHijo);

	if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja
			&& archivo->DeterminarEstadoNodo(hijo)
					== eEstadoCargaNodo_CargaMinima) {

		while (hijo->ObtenerCantidadRegistros() != 0)
			_nodoInterno->AgregarRegistro(hijo->QuitarRegistro());

		archivo->LiberarNodo(nroHijo);

		if (_nodoInterno->ObtenerHijoDerecho() == nroHijo)
			_nodoInterno->EstablecerHijoDerecho(0);
		else
			_nodoInterno->EstablecerHijoIzquierdo(0);

		if (_nodoInterno->ObtenerHijoDerecho()
				!= _nodoInterno->ObtenerHijoIzquierdo())
			archivo->EscribirNodo(_nroNodoInterno, _nodoInterno);
		else {

			hojaNueva = NodoArbolPuntoOptimoFactory_Nuevo(
					eNodoArbolPuntoOptimo_Hoja);

			while (_nodoInterno->ObtenerCantidadRegistros() != 0)
				hojaNueva->AgregarRegistro(_nodoInterno->QuitarRegistro());

			archivo->EscribirNodo(_nroNodoInterno, hojaNueva); /**Conversión de nodo interno a hoja**/
		}
	}

	else {

		while (archivo->DeterminarEstadoNodo(_nodoInterno)
				== eEstadoCargaNodo_Underflow)
			_nodoInterno->AgregarRegistro(hijo->QuitarRegistro());

		if (archivo->DeterminarEstadoNodo(hijo) != eEstadoCargaNodo_Underflow) {

			archivo->EscribirNodo(_nroNodoInterno, _nodoInterno);
			archivo->EscribirNodo(nroHijo, hijo);

		} else if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Interno) {

			archivo->EscribirNodo(_nroNodoInterno, _nodoInterno);
			ResolverUnderflow(nroHijo,
					(iNodoArbolPuntoOptimoNodoInternoPtr) hijo);

		} else
			ResolverUnderflow(_nroNodoInterno, _nodoInterno, nroHijo,
					(iNodoArbolPuntoOptimoNodoHojaPtr) hijo);
	}

	hijo->Dispose();

	if (hojaNueva)
		hojaNueva->Dispose();
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoInterno,
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno, size_t _nroHoja,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

	iNodoArbolPuntoOptimoPtr pHermano = NULL;
	iNodoArbolPuntoOptimoPtr* ppHermano = &pHermano;
	iNodoArbolPuntoOptimoNodoHojaPtr hojaNueva = NULL;

	if ((archivo->DeterminarPorcentajeCarga(_nodoInterno)
			+ archivo->DeterminarPorcentajeCarga(_hoja)) <= 100) {

		while (_hoja->ObtenerCantidadRegistros() != 0)
			_nodoInterno->AgregarRegistro(_hoja->QuitarRegistro());

		archivo->LiberarNodo(_nroHoja);

		if (_nodoInterno->ObtenerHijoDerecho() == _nroHoja)
			_nodoInterno->EstablecerHijoDerecho(0);
		else
			_nodoInterno->EstablecerHijoIzquierdo(0);

		if (_nodoInterno->ObtenerHijoDerecho()
				!= _nodoInterno->ObtenerHijoIzquierdo())
			archivo->EscribirNodo(_nroNodoInterno, _nodoInterno);
		else {

			hojaNueva = NodoArbolPuntoOptimoFactory_Nuevo(
					eNodoArbolPuntoOptimo_Hoja);

			while (_nodoInterno->ObtenerCantidadRegistros() != 0)
				hojaNueva->AgregarRegistro(_nodoInterno->QuitarRegistro());

			archivo->EscribirNodo(_nroNodoInterno, hojaNueva);
		}
	}

	else if (ObtenerHermano(_nodoInterno, _nroHoja, ppHermano)
			== eHermanoVpTree_ABM__NodoInterno) {

		archivo->EscribirNodo(_nroNodoInterno, (*ppHermano));/**Pisamos al padre con el hermano**/
		archivo->LiberarNodo(_nodoInterno->ObtenerHijoDerecho());/**Liberamos ambos hermanos**/
		archivo->LiberarNodo(_nodoInterno->ObtenerHijoIzquierdo());

		while (_nodoInterno->ObtenerCantidadRegistros() != 0)
			Alta(_nodoInterno->QuitarRegistro());

		while (_hoja->ObtenerCantidadRegistros() != 0)
			Alta(_hoja->QuitarRegistro());
	}

	else {

		hojaNueva = NodoArbolPuntoOptimoFactory_Nuevo(
				eNodoArbolPuntoOptimo_Hoja);

		while (_nodoInterno->ObtenerCantidadRegistros() != 0)
			hojaNueva->AgregarRegistro(_nodoInterno->QuitarRegistro());

		while (_hoja->ObtenerCantidadRegistros() != 0)
			hojaNueva->AgregarRegistro((_hoja->QuitarRegistro()));

		if ((*ppHermano))
			while ((*ppHermano)->ObtenerCantidadRegistros() != 0)
				hojaNueva->AgregarRegistro((*ppHermano)->QuitarRegistro());

		if (_nodoInterno->ObtenerHijoDerecho() != 0)
			archivo->LiberarNodo(_nodoInterno->ObtenerHijoDerecho());

		if (_nodoInterno->ObtenerHijoIzquierdo() != 0)
			archivo->LiberarNodo(_nodoInterno->ObtenerHijoIzquierdo());

		if (archivo->DeterminarEstadoNodo(hojaNueva)
				== eEstadoCargaNodo_Overflow)
			ResolverOverflow(_nroNodoInterno, hojaNueva);/**Conversión de nodo interno a hoja**/
		else
			archivo->EscribirNodo(_nroNodoInterno, hojaNueva);/**Conversión de nodo interno a hoja**/
	}

	if ((*ppHermano))
		(*ppHermano)->Dispose();

	if (hojaNueva)
		hojaNueva->Dispose();
}

void VpTree_ABM::ResolverOverflow(size_t _nroHoja,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

}

eHermanoVpTree_ABM VpTree_ABM::ObtenerHermano(
		iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _hijo,
		iNodoArbolPuntoOptimoPtr* _hermano) {

	size_t hermano;

	if (_padre->ObtenerHijoDerecho() == _hijo)
		hermano = _padre->ObtenerHijoIzquierdo();
	else
		hermano = _padre->ObtenerHijoDerecho();

	if (hermano == 0) {

		*_hermano = NULL;
		return eHermanoVpTree_ABM__Inexistente;
	}

	*_hermano = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(hermano);

	if ((*_hermano)->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja)
		return eHermanoVpTree_ABM__Hoja;
	else
		return eHermanoVpTree_ABM__NodoInterno;
}

size_t VpTree_ABM::GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {
	size_t cantidad = _hoja->ObtenerCantidadRegistros();
	size_t listaClaves[cantidad];

	for (size_t i = 0; i < cantidad; i++)
		listaClaves[i] =
				_hoja->ObtenerRegistro(i)->GetFeature(0)->AsNumber().entero.enteroSinSigno.entero32SinSigno;

	return this->espacioMetrico->CalcularPivote(listaClaves, cantidad);
}

float VpTree_ABM::CalcularRadio(iFeaturePtr _pivote,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

	return 0;
}

eResultadoVpTree_ABM VpTree_ABM::Alta(iRegistroPtr _reg) {

	return eResultadoVpTree_ABM__Ok;
}

eResultadoVpTree_ABM VpTree_ABM::Baja(iFeaturePtr _key) {

	return eResultadoVpTree_ABM__Ok;
}

eResultadoVpTree_ABM VpTree_ABM::Modificacion(iRegistroPtr _reg) {

	return eResultadoVpTree_ABM__Ok;
}

eResultadoVpTree_ABM VpTree_ABM::Buscar(iRegistroPtr _reg) {

	return eResultadoVpTree_ABM__Ok;
}

