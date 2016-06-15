#include <stdlib.h>

#include "../Headers/ComandoAlta.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"
#include "../../../Memoria/Registro/RegistroFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Memoria/DescriptorRegistro/DescriptorRegistroFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

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
	fprintf(salida, "%s: n t s i r\n", this->ObtenerNombre());
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
		this->ImprimirAyuda(salida);
		return;
	}

	const char *nombreArchivo = listaParametros[0];
	size_t tamanioBloque = strtoull(listaParametros[1], NULL, 0);
	size_t nroCampo = strtoull(listaParametros[3], NULL, 0);

	iDescriptorRegistroPtr descRegistro = DescriptorRegistroFactory_Nuevo(listaParametros[2]);
	if (!descRegistro)
	{
		fprintf(salida, "ERROR!! El formato del descriptor de registro provisto no es valido.\n");
		return;
	}
	
	if (!descRegistro->ObtenerCantidadCampos())
	{
		descRegistro->Dispose();
		fprintf(salida, "ERROR!! El descriptor no tiene campos!!.\n");
		return;
	}
	
	iRegistroPtr registro = RegistroFactory_Nuevo(descRegistro, listaParametros[4]);
	descRegistro->Dispose();

	iVpTree_ABMPtr vpTree = NULL;
	Sistema_Execute(vpTree = VpTree_ABMFactory_Nuevo(nombreArchivo, nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16););

	eResultadoVpTree_ABM resultado;
	Sistema_Execute(resultado = vpTree->Alta(registro, true););

	if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok)
		fprintf(salida, "La operacion se ha completado con exito.\n");
	else if(resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Duplicado)
	{
		fprintf(salida, "ERROR!! Ya existe un registro con esa clave.\n");
		registro->Dispose();
	}

	vpTree->Dispose();
}
