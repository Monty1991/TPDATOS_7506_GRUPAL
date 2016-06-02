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

	raiz = archivo->LeerNodo(0);

	if (raiz == NULL) {

		raiz = NodoArbolPuntoOptimoFactory_Nuevo(eNodoArbolPuntoOptimo_Hoja);
		archivo->EscribirNodo(0, raiz);
	}

	estado = eEstadoVpTree_ABM__Ok;
}

void VpTree_ABM::ResolverEstado(size_t _nroNodoInterno,
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno, size_t _nroHoja,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

	switch (estado) {

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

	estado = eEstadoVpTree_ABM__Ok;
}

void VpTree_ABM::ResolverUnderflow(size_t _nroNodoInterno,
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno) {

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

iNodoPtr VpTree_ABM::LeerIzq(iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno) {

	return NULL;
}

iNodoPtr VpTree_ABM::LeerDer(iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno) {

	return NULL;
}
