#include <stdlib.h>
#include <string.h>

#include "../Headers/ComandoBaja.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"
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
	fprintf(salida, "baja: n t s i c\n");
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
		fprintf(salida, "ERROR!! Se esperaban al menos 5 parametros\n");
		return;
	}

	size_t tamanioBloque = strtoull(listaParametros[1], NULL, 0);
	size_t nroCampo = strtoull(listaParametros[3], NULL, 0);
	iVpTree_ABMPtr vpTree = VpTree_ABMFactory_Nuevo(listaParametros[0], nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16);

	iFeaturePtr clave = NULL;

	if (false)
	{
		sCadenaANSI cadena;
		cadena.cadena = (char *)listaParametros[4];
		cadena.largo = strlen(cadena.cadena);
		clave = FeatureFactory_Nuevo(&cadena);
	}
	else if (false)
	{
		uValue value;
		value.primitivo.numero.entero.enteroSinSigno.entero32SinSigno = strtoul(listaParametros[4], NULL, 0);
		clave = FeatureFactory_Nuevo(value, eValueType::eValueType_U4);
	}

	eResultadoVpTree_ABM resultado = vpTree->Baja(clave);
	if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok)
		fprintf(salida, "La operacion se ha completado con exito\n");
	else if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Inexistente)
		fprintf(salida, "ERROR!! No existe un registro con esa clave. Ya lo habia borrado antes?\n");

	clave->Dispose();
}
