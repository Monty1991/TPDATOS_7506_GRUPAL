#include "../Headers/HidratadorNodoArbolPuntoOptimo.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../HidratadorFeature/HidratadorFeatureFactory.h"
#include "../../HidratadorRegistro/HidratadorRegistroFactory.h"
#include "../../../Utils/NodoArbolPuntoOptimo/NodoArbolPuntoOptimoFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

HidratadorNodoArbolPuntoOptimo::HidratadorNodoArbolPuntoOptimo()
{
	this->hidratadorFeature = HidratadorFeatureFactory_Nuevo();
	this->hidratadorRegistro = HidratadorRegistroFactory_Nuevo();
}

HidratadorNodoArbolPuntoOptimo::~HidratadorNodoArbolPuntoOptimo()
{
	if (this->hidratadorFeature)
		this->hidratadorFeature->Dispose();

	if (this->hidratadorRegistro)
		this->hidratadorRegistro->Dispose();	
}

size_t HidratadorNodoArbolPuntoOptimo::Hidratar(char *buff, iNodoPtr *nodo)
{
	size_t leido = 0;

	uNumber numero;
	numero.entero.enteroSinSigno.entero64SinSigno = 0;

	Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &numero, eValueType::eValueType_U1););
	eNodoArbolPuntoOptimo tipo = (eNodoArbolPuntoOptimo) numero.entero.enteroSinSigno.entero8SinSigno;

	iFeaturePtr pivote = NULL;
	float radio = 0;
	size_t hijoIzquierdo = 0;
	size_t hijoDerecho = 0;
	
	if (tipo == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)
	{
		Sistema_Execute(leido += this->hidratadorFeature->Hidratar(buff + leido, &pivote););

		Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &numero, eValueType::eValueType_F32););
		radio = numero.flotante.flotante32;

		Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &numero, eValueType::eValueType_U4););
		hijoIzquierdo = numero.entero.enteroSinSigno.entero32SinSigno;

		Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &numero, eValueType::eValueType_U4););
		hijoDerecho = numero.entero.enteroSinSigno.entero32SinSigno;
	}
	
	Sistema_Execute(leido += NumberUtils_Hidratar(buff + leido, &numero, eValueType::eValueType_U1););
	size_t cantidadRegistros = numero.entero.enteroSinSigno.entero8SinSigno;

	iRegistroPtr tablaRegistros[cantidadRegistros];

	for (size_t i = 0; i < cantidadRegistros; i++)
		Sistema_Execute(leido += this->hidratadorRegistro->Hidratar(buff + leido, tablaRegistros + i););

	*nodo = NodoArbolPuntoOptimoFactory_Nuevo(tipo, tablaRegistros, cantidadRegistros);

	if (tipo == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)
	{
		iNodoArbolPuntoOptimoNodoInternoPtr nodoArbolPuntoOptimoNodoInternoPtr = ((iNodoArbolPuntoOptimoNodoInternoPtr)(*nodo));
		nodoArbolPuntoOptimoNodoInternoPtr->EstablecerPivote(pivote);
		nodoArbolPuntoOptimoNodoInternoPtr->EstablecerRadio(radio);
		nodoArbolPuntoOptimoNodoInternoPtr->EstablecerHijoIzquierdo(hijoIzquierdo);
		nodoArbolPuntoOptimoNodoInternoPtr->EstablecerHijoDerecho(hijoDerecho);
	}

	return leido;
}

void HidratadorNodoArbolPuntoOptimo::Dispose()
{
	delete this;
}
