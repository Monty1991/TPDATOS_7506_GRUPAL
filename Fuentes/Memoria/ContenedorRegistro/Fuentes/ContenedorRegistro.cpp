#include "../Headers/ContenedorRegistro.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"
#include "../../../Exceptions/ExceptionFactory.h"

ContenedorRegistro::ContenedorRegistro(iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	this->cantidadRegistros = cantidadRegistros;
	this->tamanioTablaRegistros = 16;
	// con esto nos aseguramos de que la tabla sea potencia de 2
	while (this->tamanioTablaRegistros < this->cantidadRegistros)
		this->tamanioTablaRegistros *= 2;

	this->tablaRegistros = new iRegistroPtr[this->tamanioTablaRegistros];

	for (size_t i = 0; i < this->cantidadRegistros; i++)
		this->tablaRegistros[i] = listaRegistros[i];
}

ContenedorRegistro::~ContenedorRegistro()
{
	if (this->tablaRegistros)
	{
		for (size_t i = 0; i < this->cantidadRegistros; i++)
		{
			iRegistroPtr reg = this->tablaRegistros[i];
			if (reg)
				reg->Dispose();
		}
	}

	delete[] this->tablaRegistros;
	this->tablaRegistros = NULL;
}

void ContenedorRegistro::Dispose()
{
	delete this;
}

size_t ContenedorRegistro::ObtenerCantidadRegistros()
{
	return this->cantidadRegistros;
}

iRegistroPtr ContenedorRegistro::ObtenerRegistro(size_t pos)
{
	if (pos >= this->cantidadRegistros)
	{
		char msg[20];
		StringUtils_Concatenar(msg, "%lu", pos);
		Throw(ExceptionType_ArrayIndexOutOfBounds, msg);
	}

	return this->tablaRegistros[pos];
}

void ContenedorRegistro::AgregarRegistro(iRegistroPtr reg)
{
	this->tablaRegistros[this->cantidadRegistros++] = reg;
	if (this->cantidadRegistros >= this->tamanioTablaRegistros)
		this->RedimensionarTabla(this->tamanioTablaRegistros * 2);
}

iRegistroPtr ContenedorRegistro::QuitarRegistro(size_t pos)
{
	iRegistroPtr reg = NULL;
	Sistema_Execute(reg = this->ObtenerRegistro(pos););

	for (size_t i = pos; i < (this->cantidadRegistros - 1); i++)
		Sistema_Execute(this->tablaRegistros[i] = this->ObtenerRegistro(i + 1););

	this->cantidadRegistros--;

	if (this->cantidadRegistros * 4 <= this->tamanioTablaRegistros)
		this->RedimensionarTabla(this->tamanioTablaRegistros / 2);

	return reg;
}

iRegistroPtr ContenedorRegistro::QuitarRegistro()
{
	return this->QuitarRegistro(0);
}

size_t ContenedorRegistro::BuscarRegistro(iFeaturePtr clave, size_t nroCampoClave)
{
	for (size_t i = 0; i < this->cantidadRegistros; i++)
	{
		iFeaturePtr key = NULL;
		Sistema_Execute(key = this->tablaRegistros[i]->GetFeature(nroCampoClave););

		int resultado;
		Sistema_Execute(resultado = clave->Comparar(key););

		if (!resultado)
			return i;
	}

	return this->cantidadRegistros;
}

void ContenedorRegistro::RedimensionarTabla(size_t nuevoTamanio)
{
	iRegistroPtr *nuevaTabla = new iRegistroPtr[nuevoTamanio];

	for (size_t i = 0; i < this->cantidadRegistros; i++)
		nuevaTabla[i] = this->tablaRegistros[i];

	delete [] this->tablaRegistros;
	this->tablaRegistros = nuevaTabla;
	this->tamanioTablaRegistros = nuevoTamanio;
}
