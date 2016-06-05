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

void VpTree_ABM::ResolverEstado(eEstadoVpTree_ABM _estado, size_t _nroNodoPadre,
		iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
		iNodoArbolPuntoOptimoNodoHojaPtr _hijo) {

	switch (_estado) {

	case eEstadoVpTree_ABM__HojaEnOverflow:
		ResolverOverflow(_nroNodoHijo, _hijo);
		break;

	case eEstadoVpTree_ABM__HojaEnUnderflow:
		ResolverUnderflow(_nroNodoPadre, _padre, _nroNodoHijo, _hijo);
		break;

	case eEstadoVpTree_ABM__NodoInternoEnUnderflow:
		ResolverUnderflow(_nroNodoPadre, _padre);
		break;
	}
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoPadre,
		iNodoArbolPuntoOptimoNodoInternoPtr _padre) {

	size_t nroNodoHijo;
	iNodoArbolPuntoOptimoPtr hijo = NULL;
	iNodoArbolPuntoOptimoNodoHojaPtr hojaNueva = NULL;

	if ((nroNodoHijo = _padre->ObtenerHijoDerecho()) == 0)
		if ((nroNodoHijo = _padre->ObtenerHijoIzquierdo()) == 0)
			Throw(" ", "Nodo interno sin hijos.");

	hijo = (iNodoArbolPuntoOptimoPtr) archivo->LeerNodo(nroNodoHijo);

	if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Hoja
			&& archivo->DeterminarEstadoNodo(hijo)
					== eEstadoCargaNodo_CargaMinima) {

		while (hijo->ObtenerCantidadRegistros())
			_padre->AgregarRegistro(hijo->QuitarRegistro());

		archivo->LiberarNodo(nroNodoHijo);

		if (_padre->ObtenerHijoDerecho() == nroNodoHijo)
			_padre->EstablecerHijoDerecho(0);
		else
			_padre->EstablecerHijoIzquierdo(0);

		if (_padre->ObtenerHijoDerecho() != _padre->ObtenerHijoIzquierdo())
			archivo->EscribirNodo(_nroNodoPadre, _padre);
		else {

			hojaNueva = NodoArbolPuntoOptimoFactory_Nuevo(
					eNodoArbolPuntoOptimo_Hoja);

			while (_padre->ObtenerCantidadRegistros())
				hojaNueva->AgregarRegistro(_padre->QuitarRegistro());

			archivo->EscribirNodo(_nroNodoPadre, hojaNueva);
		}
	}

	else {

		while (archivo->DeterminarEstadoNodo(_padre)
				== eEstadoCargaNodo_Underflow)
			_padre->AgregarRegistro(hijo->QuitarRegistro());

		if (archivo->DeterminarEstadoNodo(hijo) != eEstadoCargaNodo_Underflow) {

			archivo->EscribirNodo(_nroNodoPadre, _padre);
			archivo->EscribirNodo(nroNodoHijo, hijo);

		} else if (hijo->ObtenerTipoNodo() == eNodoArbolPuntoOptimo_Interno) {

			archivo->EscribirNodo(_nroNodoPadre, _padre);
			ResolverUnderflow(nroNodoHijo,
					(iNodoArbolPuntoOptimoNodoInternoPtr) hijo);

		} else
			ResolverUnderflow(_nroNodoPadre, _padre, nroNodoHijo,
					(iNodoArbolPuntoOptimoNodoHojaPtr) hijo);
	}

	hijo->Dispose();

	if (hojaNueva)
		hojaNueva->Dispose();
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoPadre,
		iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
		iNodoArbolPuntoOptimoNodoHojaPtr _hijo) {

	size_t nroNodoHermano = 0;
	size_t* pNroNodoHermano = &nroNodoHermano;
	iNodoArbolPuntoOptimoPtr pHermano = NULL;
	iNodoArbolPuntoOptimoPtr* ppHermano = &pHermano;
	iNodoArbolPuntoOptimoNodoHojaPtr hojaNueva = NULL;

	if ((archivo->DeterminarPorcentajeCarga(_padre)
			+ archivo->DeterminarPorcentajeCarga(_hijo)) <= 100) {

		while (_hijo->ObtenerCantidadRegistros())
			_padre->AgregarRegistro(_hijo->QuitarRegistro());

		archivo->LiberarNodo(_nroNodoHijo);

		if (_padre->ObtenerHijoDerecho() == _nroNodoHijo)
			_padre->EstablecerHijoDerecho(0);
		else
			_padre->EstablecerHijoIzquierdo(0);

		if (_padre->ObtenerHijoDerecho() != _padre->ObtenerHijoIzquierdo())
			archivo->EscribirNodo(_nroNodoPadre, _padre);
		else {

			hojaNueva = NodoArbolPuntoOptimoFactory_Nuevo(
					eNodoArbolPuntoOptimo_Hoja);

			while (_padre->ObtenerCantidadRegistros())
				hojaNueva->AgregarRegistro(_padre->QuitarRegistro());

			archivo->EscribirNodo(_nroNodoPadre, hojaNueva);
		}
	}

	else if (ObtenerHermano(_padre, _nroNodoHijo, pNroNodoHermano, ppHermano)
			== eHermanoVpTree_ABM__NodoInterno) {

		archivo->EscribirNodo(_nroNodoPadre, (*ppHermano));
		archivo->LiberarNodo(_nroNodoHijo);
		archivo->LiberarNodo(nroNodoHermano);

		while (_padre->ObtenerCantidadRegistros())
			Alta(_padre->QuitarRegistro());

		while (_hijo->ObtenerCantidadRegistros())
			Alta(_hijo->QuitarRegistro());
	}

	else {

		hojaNueva = NodoArbolPuntoOptimoFactory_Nuevo(
				eNodoArbolPuntoOptimo_Hoja);

		while (_padre->ObtenerCantidadRegistros())
			hojaNueva->AgregarRegistro(_padre->QuitarRegistro());

		while (_hijo->ObtenerCantidadRegistros())
			hojaNueva->AgregarRegistro((_hijo->QuitarRegistro()));

		if ((*ppHermano))
			while ((*ppHermano)->ObtenerCantidadRegistros())
				hojaNueva->AgregarRegistro((*ppHermano)->QuitarRegistro());

		archivo->LiberarNodo(_nroNodoHijo);

		if (nroNodoHermano)
			archivo->LiberarNodo(nroNodoHermano);

		if (archivo->DeterminarEstadoNodo(hojaNueva)
				== eEstadoCargaNodo_Overflow)
			ResolverOverflow(_nroNodoPadre, hojaNueva);
		else
			archivo->EscribirNodo(_nroNodoPadre, hojaNueva);
	}

	if ((*ppHermano))
		(*ppHermano)->Dispose();

	if (hojaNueva)
		hojaNueva->Dispose();
}

void VpTree_ABM::ResolverOverflow(size_t _nroNodoHijo,
		iNodoArbolPuntoOptimoNodoHojaPtr _hijo) {

}

iNodoArbolPuntoOptimoPtr VpTree_ABM::Fusionar(
		iNodoArbolPuntoOptimoNodoInternoPtr _padre, size_t _nroNodoHijo,
		iNodoArbolPuntoOptimoNodoHojaPtr _hijo) {

	iNodoArbolPuntoOptimoPtr padreNuevo = NULL;

	if (_padre->ObtenerHijoDerecho() == _nroNodoHijo)
		_padre->EstablecerHijoDerecho(0);
	else if (_padre->ObtenerHijoIzquierdo() == _nroNodoHijo)
		_padre->EstablecerHijoIzquierdo(0);
	else
		Throw(" ", "No es hijo del padre");

	if (_padre->ObtenerHijoDerecho() == _padre->ObtenerHijoIzquierdo())
		padreNuevo = NodoArbolPuntoOptimoFactory_Nuevo(
				eNodoArbolPuntoOptimo_Hoja);
	else {

		padreNuevo = NodoArbolPuntoOptimoFactory_Nuevo(
				eNodoArbolPuntoOptimo_Interno);

		((iNodoArbolPuntoOptimoNodoInternoPtr) padreNuevo)->EstablecerPivote(
				_padre->ObtenerPivote());
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

