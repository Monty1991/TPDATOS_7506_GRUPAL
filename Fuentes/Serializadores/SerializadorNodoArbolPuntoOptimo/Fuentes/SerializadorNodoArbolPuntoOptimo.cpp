#include "../Headers/SerializadorNodoArbolPuntoOptimo.h"
#include "../../SerializadorRegistro/SerializadorRegistroFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Utils/NumberUtils/Headers/NumberUtils.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"
#include "../../../Utils/NodoArbolPuntoOptimo/Headers/iNodoArbolPuntoOptimo.h"

SerializadorNodoArbolPuntoOptimo::SerializadorNodoArbolPuntoOptimo()
{
	this->serializadorRegistro = SerializadorRegistroFactory_Nuevo();
}

SerializadorNodoArbolPuntoOptimo::~SerializadorNodoArbolPuntoOptimo()
{
	if (this->serializadorRegistro)
		this->serializadorRegistro->Dispose();	
}

size_t SerializadorNodoArbolPuntoOptimo::CalcularEspacioSerializacion(iNodoPtr nodo)
{
	size_t espacio = 0;
	size_t cantidadRegistros = nodo->ObtenerCantidadRegistros();

	iNodoArbolPuntoOptimoNodoHojaPtr nodoArbolPuntoOptimoNodoHoja = (iNodoArbolPuntoOptimoNodoHojaPtr)nodo;

	eNodoArbolPuntoOptimo tipoNodo = nodoArbolPuntoOptimoNodoHoja->ObtenerTipoNodo();
	espacio += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U1);

	if (tipoNodo == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)
	{
		iNodoArbolPuntoOptimoNodoInternoPtr nodoArbolPuntoOptimoNodoInterno = (iNodoArbolPuntoOptimoNodoInternoPtr)nodoArbolPuntoOptimoNodoHoja;

		iFeaturePtr pivote = nodoArbolPuntoOptimoNodoInterno->ObtenerPivote();

		Sistema_Execute(espacio += FeatureFactory_CalcularEspacioSerializacion(pivote););
		Sistema_Execute(espacio += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_F32););
		Sistema_Execute(espacio += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U4););
		Sistema_Execute(espacio += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U4););
	}

	Sistema_Execute(espacio += NumberUtils_CalcularEspacioSerializacion(eValueType::eValueType_U1););

	for (size_t i = 0; i < cantidadRegistros; i++)
		Sistema_Execute(espacio += this->serializadorRegistro->CalcularEspacio(nodo->ObtenerRegistro(i)););

	return espacio;
}

size_t SerializadorNodoArbolPuntoOptimo::Serializar(char *buff, iNodoPtr nodo)
{
	size_t espacio = 0;
	size_t cantidadRegistros = nodo->ObtenerCantidadRegistros();

	iNodoArbolPuntoOptimoNodoHojaPtr nodoArbolPuntoOptimoNodoHoja = (iNodoArbolPuntoOptimoNodoHojaPtr)nodo;

	eNodoArbolPuntoOptimo tipoNodo = nodoArbolPuntoOptimoNodoHoja->ObtenerTipoNodo();
	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = tipoNodo;
	Sistema_Execute(espacio += NumberUtils_Serializar(buff + espacio, number, eValueType::eValueType_U1););

	if (tipoNodo == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)
	{
		iNodoArbolPuntoOptimoNodoInternoPtr nodoArbolPuntoOptimoNodoInterno = (iNodoArbolPuntoOptimoNodoInternoPtr)nodoArbolPuntoOptimoNodoHoja;

		iFeaturePtr pivote = nodoArbolPuntoOptimoNodoInterno->ObtenerPivote();
		Sistema_Execute(espacio += FeatureFactory_Serializar(buff + espacio, pivote););

		number.flotante.flotante32 = nodoArbolPuntoOptimoNodoInterno->ObtenerRadio();
		Sistema_Execute(espacio += NumberUtils_Serializar(buff + espacio, number, eValueType::eValueType_F32););

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerHijoIzquierdo();
		Sistema_Execute(espacio += NumberUtils_Serializar(buff + espacio, number, eValueType::eValueType_U4););

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerHijoDerecho();
		Sistema_Execute(espacio += NumberUtils_Serializar(buff + espacio, number, eValueType::eValueType_U4););
	}

	number.entero.enteroSinSigno.entero8SinSigno = cantidadRegistros;
	Sistema_Execute(espacio += NumberUtils_Serializar(buff + espacio, number, eValueType::eValueType_U1););

	for (size_t i = 0; i < cantidadRegistros; i++)
		Sistema_Execute(espacio += this->serializadorRegistro->Serializar(buff + espacio, nodo->ObtenerRegistro(i)););

	return espacio;
}

void SerializadorNodoArbolPuntoOptimo::Dispose()
{
	delete this;
}
