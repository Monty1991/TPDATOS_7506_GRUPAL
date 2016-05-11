#include "../Headers/SerializadorNodo.h"
#include "../../SerializadorRegistro/SerializadorRegistroFactory.h"

SerializadorNodo::SerializadorNodo()
{
	this->serializadorRegistro = SerializadorRegistroFactory_Nuevo();
}

SerializadorNodo::~SerializadorNodo()
{
	if (this->serializadorNumerico)
		this->serializadorNumerico->Dispose();

	if (this->serializadorRegistro)
		this->serializadorRegistro->Dispose();
}

size_t SerializadorNodo::CalcularEspacioSerializacion(iNodoPtr nodo)
{
	size_t espacio = 0;
	size_t cantidadRegistros = nodo->ObtenerCantidadRegistros();
	for (size_t i = 0; i < cantidadRegistros; i++)
		espacio += this->serializadorRegistro->CalcularEspacio(nodo->ObtenerRegistro(i));
}

size_t SerializadorNodo::Serializar(char *buff, iNodoPtr nodo)
{
	size_t escrito = 0;
	uNumber estado;
	estado.entero.enteroSinSigno.entero8SinSigno = nodo->ObtenerTipoNodo();
	escrito += this->serializadorNumerico->Serializar(buff, estado, eValueType::eValueType_U1);

	for (size_t i = 0; i < nodo->ObtenerCantidadRegistros(); i++)
		escrito += this->serializadorRegistro->Serializar(buff + escrito, nodo->ObtenerRegistro(i));

//	TODO: Agregar serializacion del pivote y referencias, en caso de ser interno
	
	return escrito;
}

void SerializadorNodo::Dispose()
{
	delete this;
}
