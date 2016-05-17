#include "../Headers/HidratadorNodo.h"
#include "../../HidratadorNumerico/HidratadorNumericoFactory.h"
#include "../../HidratadorRegistro/HidratadorRegistroFactory.h"
#include "../../../Utils/Nodo/NodoFactory.h"

HidratadorNodo::HidratadorNodo()
{
	this->hidratadorNumerico = HidratadorNumericoFactory_Nuevo();
	this->hidratadorRegistro = HidratadorRegistroFactory_Nuevo();
}

HidratadorNodo::~HidratadorNodo()
{
	if (this->hidratadorNumerico)
		this->hidratadorNumerico->Dispose();

	if (this->hidratadorRegistro)
		this->hidratadorRegistro->Dispose();
}

size_t HidratadorNodo::Hidratar(char *buff, iNodoPtr *nodo)
{
	size_t leido = 0;

	uNumber numero;
	leido += this->hidratadorNumerico->Hidratar(buff + leido, &numero, eValueType::eValueType_U1);
	eTipoNodo tipo = (eTipoNodo) numero.entero.enteroSinSigno.entero8SinSigno;

	leido += this->hidratadorNumerico->Hidratar(buff + leido, &numero, eValueType::eValueType_U1);
	size_t cantidadRegistros = numero.entero.enteroSinSigno.entero8SinSigno;

	// TODO: agregar para el caso del nodo interno
	
	iRegistroPtr *tablaRegistros = new iRegistroPtr[cantidadRegistros];

	for (size_t i = 0; i < cantidadRegistros; i++)
		leido += this->hidratadorRegistro->Hidratar(buff + leido, tablaRegistros + i);

	*nodo = NodoFactory_Nuevo(tipo, tablaRegistros, cantidadRegistros);

	delete [] tablaRegistros;
	
	return leido;
}

void HidratadorNodo::Dispose()
{
	delete this;
}
