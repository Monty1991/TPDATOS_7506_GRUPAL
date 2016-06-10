#include <stdlib.h>

#include "../Headers/ComandoAlta.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"

ComandoAlta::ComandoAlta()
{

}

ComandoAlta::~ComandoAlta()
{

}

void ComandoAlta::Dispose()
{
	delete this;
}

const char *ComandoAlta::ObtenerNombre()
{
	return "alta";
}

void ComandoAlta::ImprimirAyuda(FILE *salida)
{
	fprintf(salida, "alta: n t s i r\n");
	fprintf(salida, "\tn: nombre archivo de datos\n");
	fprintf(salida, "\tt: tamanio de bloque, en bytes\n");
	fprintf(salida, "\ts: schema de registro, ver documentacion\n");
	fprintf(salida, "\ti: nro de campo que contiene la clave\n");
	fprintf(salida, "\tr: registro, siguiendo el formato del schema\n");
}

void ComandoAlta::Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad)
{
	if (cantidad < 5)
	{
		fprintf(salida, "ERROR!! Se esperaban al menos 5 parametros");
		return;
	}

	size_t tamanioBloque = strtoull(listaParametros[1], NULL, 0);
	size_t nroCampo = strtoull(listaParametros[3], NULL, 0);
	iVpTree_ABMPtr vpTree = VpTree_ABMFactory_Nuevo(listaParametros[0], nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16);

	vpTree->Alta(NULL,true);
}
