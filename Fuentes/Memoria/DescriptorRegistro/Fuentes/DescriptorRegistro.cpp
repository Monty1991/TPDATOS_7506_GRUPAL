#include "../Headers/DescriptorRegistro.h"

DescriptorRegistro::DescriptorRegistro(sDescriptorCampoPtr *tablaDescriptorCampo, size_t cantidadDescriptoresCampo): cantidadDescriptoresCampo(cantidadDescriptoresCampo)
{
	this->tablaDescriptorCampo = new sDescriptorCampoPtr[this->cantidadDescriptoresCampo];
	for(size_t i = 0; i < this->cantidadDescriptoresCampo; i++)
		this->tablaDescriptorCampo[i] = tablaDescriptorCampo[i];
}

DescriptorRegistro::~DescriptorRegistro()
{
	if (this->tablaDescriptorCampo)
	{
		for(size_t i = 0; i < this->cantidadDescriptoresCampo; i++)
			delete this->tablaDescriptorCampo[i];

		delete [] this->tablaDescriptorCampo;
	}
}

void DescriptorRegistro::Dispose()
{
	delete this;
}

size_t DescriptorRegistro::ObtenerCantidadCampos()
{
	return this->cantidadDescriptoresCampo;
}

sDescriptorCampoPtr DescriptorRegistro::ObtenerDescriptorCampo(size_t pos)
{
	if (pos > this->cantidadDescriptoresCampo)
		return NULL;

	return this->tablaDescriptorCampo[pos];
}
