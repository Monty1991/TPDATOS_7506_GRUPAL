/*
 * VpTree_ABM.cpp
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#include "../Headers/VpTree_ABM.h"
#include "../../../io/ArchivoArbol/ArchivoArbolFactory.h"

VpTree_ABM::~VpTree_ABM() {

	if (raiz) {

		raiz->Dispose();
		raiz = NULL;
	}

	if (archivo) {

		archivo->Close();
		archivo = NULL;
	}

	if (fnDistancia) {

		fnDistancia->Dispose();
		fnDistancia = NULL;
	}
}

void VpTree_ABM::Dispose() {

	delete this;
}

VpTree_ABM::VpTree_ABM(const char* _fileName, iDistanceFnPtr _fnDistancia,
		size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia) {

	fnDistancia = _fnDistancia->Clone();

	archivo = ArchivoArbolFactory_Nuevo(_fileName, _tamanioNodo, _cargaMinima,
			_tolerancia, eTipoArbol_ArbolPuntoOptimo);

	raiz = archivo->LeerNodo(0); //Revisar
}

void VpTree_ABM::ResolverEstado(eEstadoVpTree_ABM _estado,
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

}

void VpTree_ABM::ResolverUnderflow(
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno) {

}

void VpTree_ABM::ResolverUnderflow(
		iNodoArbolPuntoOptimoNodoInternoPtr _nodoInterno,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

}

void VpTree_ABM::ResolverOverflow(iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

}

iFeaturePtr VpTree_ABM::GenerarPivote(iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

	return NULL;
}

float VpTree_ABM::CalcularRadio(iFeaturePtr _pivote,
		iNodoArbolPuntoOptimoNodoHojaPtr _hoja) {

	return 0;
}

eResultadoVpTree_ABM VpTree_ABM::Alta(iRegistroPtr _reg) {

	return eResultadoVpTree_ABM_DUPLICADO;
}

eResultadoVpTree_ABM VpTree_ABM::Baja(iFeaturePtr _key) {

	return eResultadoVpTree_ABM_DUPLICADO;
}

eResultadoVpTree_ABM VpTree_ABM::Modificacion(iRegistroPtr _reg) {

	return eResultadoVpTree_ABM_DUPLICADO;
}

eResultadoVpTree_ABM VpTree_ABM::Buscar(iRegistroPtr _reg) {

	return eResultadoVpTree_ABM_DUPLICADO;
}

