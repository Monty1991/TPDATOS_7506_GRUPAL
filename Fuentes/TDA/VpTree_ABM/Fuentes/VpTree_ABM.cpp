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

	case eEstadoVpTree_ABM__Ok:
		return;

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
	iNodoArbolPuntoOptimoPtr hijo;

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

			iNodoArbolPuntoOptimoNodoHojaPtr hojaNueva =
					NodoArbolPuntoOptimoFactory_Nuevo(
							eNodoArbolPuntoOptimo_Hoja);

			while (_nodoInterno->ObtenerCantidadRegistros() != 0)
				hojaNueva->AgregarRegistro(_nodoInterno->QuitarRegistro());

			archivo->EscribirNodo(_nroNodoInterno, hojaNueva); /**Conversión de nodo interno a hoja**/
			hojaNueva->Dispose();
		}
	}

	else {

		do
			_nodoInterno->AgregarRegistro(hijo->QuitarRegistro());

		while (archivo->DeterminarEstadoNodo(_nodoInterno)
				== eEstadoCargaNodo_Underflow);

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
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoInterno,
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno, size_t _nroHoja,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

}

void VpTree_ABM::ResolverOverflow(size_t _nroHoja,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

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

