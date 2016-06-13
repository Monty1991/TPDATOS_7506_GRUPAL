#include "../Headers/DescriptorRegistro.h"

eDescriptorCampo IdentificarDescriptorCampo(char desc)
{
	switch(desc)
	{
		case 'u': case 'U':
			return eDescriptorCampo::eDescriptorCampo_U;

		case 'i': case 'I':
			return eDescriptorCampo::eDescriptorCampo_I;

		case 'f': case 'F':
			return eDescriptorCampo::eDescriptorCampo_F;

		case 'c': case 'C':
			return eDescriptorCampo::eDescriptorCampo_C;

		case 'v': case 'V':
			return eDescriptorCampo::eDescriptorCampo_CV;

		default:
			return eDescriptorCampo::eDescriptorCampo_Unknown;
	}
}

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
