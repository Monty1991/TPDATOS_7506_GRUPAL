#include <stdlib.h>

#include "../Headers/ComandoBuscar.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"

ComandoBuscar::ComandoBuscar()
{

}

ComandoBuscar::~ComandoBuscar()
{

}

void ComandoBuscar::Dispose()
{
	delete this;
}

const char *ComandoBuscar::ObtenerNombre()
{
	return "buscar";
}

void ComandoBuscar::ImprimirAyuda(FILE *salida)
{
	fprintf(salida, "buscar: n t s i c\n");
	fprintf(salida, "\tn: nombre archivo de datos\n");
	fprintf(salida, "\tt: tamanio de bloque, en bytes\n");
	fprintf(salida, "\ts: el tipo de la clave\n");
	fprintf(salida, "\ti: nro de campo que contiene la clave\n");
	fprintf(salida, "\tc: la clave\n");
}

void ComandoBuscar::Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad)
{
	if (cantidad < 5)
	{
		fprintf(salida, "ERROR!! Se esperaban al menos 5 parametros\n");
		return;
	}

	size_t tamanioBloque = strtoull(listaParametros[1], NULL, 0);
	size_t nroCampo = strtoull(listaParametros[3], NULL, 0);
	iVpTree_ABMPtr vpTree = VpTree_ABMFactory_Nuevo(listaParametros[0], nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16);

	/*
		 Requiero de la busqueda!!!!
	 */

	//	eResultadoVpTree_ABM resultado = vpTree->Buscar();
}
