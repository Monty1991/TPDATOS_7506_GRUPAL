#include <stdlib.h>
#include <string.h>

#include "../Headers/ComandoBaja.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"
#include "../../../Memoria/DescriptorRegistro/DescriptorRegistroFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"

ComandoBaja::ComandoBaja()
{

}

ComandoBaja::~ComandoBaja()
{

}

void ComandoBaja::Dispose()
{
	delete this;
}

const char *ComandoBaja::ObtenerNombre()
{
	return "baja";
}

void ComandoBaja::ImprimirAyuda(FILE *salida)
{
	fprintf(salida, "%s: n t s i c\n", this->ObtenerNombre());
	fprintf(salida, "\tn: nombre archivo de datos\n");
	fprintf(salida, "\tt: tamanio de bloque, en bytes\n");
	fprintf(salida, "\ts: tipo de la clave\n");
	fprintf(salida, "\ti: nro de campo que contiene la clave\n");
	fprintf(salida, "\tr: clave del registro\n");
}

void ComandoBaja::Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad)
{
	if (cantidad < 5)
	{
		this->ImprimirAyuda(salida);
		return;
	}

	size_t tamanioBloque = strtoull(listaParametros[1], NULL, 0);
	size_t nroCampo = strtoull(listaParametros[3], NULL, 0);

	iDescriptorRegistroPtr descRegistro = DescriptorRegistroFactory_Nuevo(listaParametros[2]);
	iFeaturePtr clave = FeatureFactory_Nuevo(descRegistro->ObtenerDescriptorCampo(0), listaParametros[4], NULL);
	descRegistro->Dispose();

	iVpTree_ABMPtr vpTree = VpTree_ABMFactory_Nuevo(listaParametros[0], nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16);
	eResultadoVpTree_ABM resultado = vpTree->Baja(clave);

	if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok)
		fprintf(salida, "La operacion se ha completado con exito.\n");
	else if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Inexistente)
		fprintf(salida, "ERROR!! No existe un registro con esa clave.\n");

	if (clave)
		clave->Dispose();

	vpTree->Dispose();
}
