#include "../Headers/DescriptorRegistro.h"

DescriptorRegistro::DescriptorRegistro(const sDescriptorCampoPtr tablaDescriptorCampo, size_t cantidadDescriptoresCampo): cantidadDescriptoresCampo(cantidadDescriptoresCampo)
{
	this->tablaDescriptorCampo = new sDescriptorCampo[this->cantidadDescriptoresCampo];
	for(size_t i = 0; i < this->cantidadDescriptoresCampo; i++)
		this->tablaDescriptorCampo[i] = tablaDescriptorCampo[i];
}

DescriptorRegistro::~DescriptorRegistro()
{
	if (this->tablaDescriptorCampo)
		delete [] this->tablaDescriptorCampo;
}

void DescriptorRegistro::Dispose()
{
	delete this;
}

size_t DescriptorRegistro::ObtenerCantidadCampos()
{
	return this->cantidadDescriptoresCampo;
}

const sDescriptorCampoPtr DescriptorRegistro::ObtenerDescriptorCampo(size_t pos)
{
	if (pos > this->cantidadDescriptoresCampo)
		return NULL;

	return (this->tablaDescriptorCampo + pos);
}
