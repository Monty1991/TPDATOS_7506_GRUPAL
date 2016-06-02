#include "../Headers/SerializadorNodoArbolPuntoOptimo.h"
#include "../../SerializadorRegistro/SerializadorRegistroFactory.h"
#include "../../SerializadorNumerico/SerializadorNumericoFactory.h"

#include "../../../Utils/NodoArbolPuntoOptimo/Headers/iNodoArbolPuntoOptimo.h"

SerializadorNodoArbolPuntoOptimo::SerializadorNodoArbolPuntoOptimo()
{
		this->serializadorRegistro = SerializadorRegistroFactory_Nuevo();
		this->serializadorNumerico = SerializadorNumericoFactory_Nuevo();
}

SerializadorNodoArbolPuntoOptimo::~SerializadorNodoArbolPuntoOptimo()
{
	if (this->serializadorNumerico)
		this->serializadorNumerico->Dispose();

	if (this->serializadorRegistro)
		this->serializadorRegistro->Dispose();	
}

size_t SerializadorNodoArbolPuntoOptimo::CalcularEspacioSerializacion(iNodoPtr nodo)
{
	size_t espacio = 0;
	size_t cantidadRegistros = nodo->ObtenerCantidadRegistros();

	iNodoArbolPuntoOptimoNodoHojaPtr nodoArbolPuntoOptimoNodoHoja = (iNodoArbolPuntoOptimoNodoHojaPtr)nodo;

	eNodoArbolPuntoOptimo tipoNodo = nodoArbolPuntoOptimoNodoHoja->ObtenerTipoNodo();
	uNumber number;
	number.entero.enteroSinSigno.entero8SinSigno = tipoNodo;
	espacio += this->serializadorNumerico->CalcularEspacio(number, eValueType::eValueType_U1);

	if (tipoNodo == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)
	{
		iNodoArbolPuntoOptimoNodoInternoPtr nodoArbolPuntoOptimoNodoInterno = (iNodoArbolPuntoOptimoNodoInternoPtr)nodoArbolPuntoOptimoNodoHoja;

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerPivote();
		espacio += this->serializadorNumerico->CalcularEspacio(number, eValueType::eValueType_U4);

		number.flotante.flotante32 = nodoArbolPuntoOptimoNodoInterno->ObtenerRadio();
		espacio += this->serializadorNumerico->CalcularEspacio(number, eValueType::eValueType_F32);

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerHijoIzquierdo();
		espacio += this->serializadorNumerico->CalcularEspacio(number, eValueType::eValueType_U4);

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerHijoDerecho();
		espacio += this->serializadorNumerico->CalcularEspacio(number, eValueType::eValueType_U4);
	}

	for (size_t i = 0; i < cantidadRegistros; i++)
		espacio += this->serializadorRegistro->CalcularEspacio(nodo->ObtenerRegistro(i));

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
	espacio += this->serializadorNumerico->Serializar(buff, number, eValueType::eValueType_U1);

	if (tipoNodo == eNodoArbolPuntoOptimo::eNodoArbolPuntoOptimo_Interno)
	{
		iNodoArbolPuntoOptimoNodoInternoPtr nodoArbolPuntoOptimoNodoInterno = (iNodoArbolPuntoOptimoNodoInternoPtr)nodoArbolPuntoOptimoNodoHoja;

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerPivote();
		espacio += this->serializadorNumerico->Serializar(buff, number, eValueType::eValueType_U4);

		number.flotante.flotante32 = nodoArbolPuntoOptimoNodoInterno->ObtenerRadio();
		espacio += this->serializadorNumerico->Serializar(buff, number, eValueType::eValueType_F32);

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerHijoIzquierdo();
		espacio += this->serializadorNumerico->Serializar(buff, number, eValueType::eValueType_U4);

		number.entero.enteroSinSigno.entero32SinSigno = nodoArbolPuntoOptimoNodoInterno->ObtenerHijoDerecho();
		espacio += this->serializadorNumerico->Serializar(buff, number, eValueType::eValueType_U4);
	}

	for (size_t i = 0; i < cantidadRegistros; i++)
		espacio += this->serializadorRegistro->Serializar(buff, nodo->ObtenerRegistro(i));

	return espacio;
}

void SerializadorNodoArbolPuntoOptimo::Dispose()
{
	delete this;
}
