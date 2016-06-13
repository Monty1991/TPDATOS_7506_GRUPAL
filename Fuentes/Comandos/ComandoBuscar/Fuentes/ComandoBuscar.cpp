#include <stdlib.h>

#include "../Headers/ComandoBuscar.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"
#include "../../../Memoria/DescriptorRegistro/DescriptorRegistroFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include <string.h>

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
		fprintf(salida, "ERROR!! Se esperaban al menos 5 parametros.\n");
		return;
	}

	size_t tamanioBloque = strtoull(listaParametros[1], NULL, 0);
	size_t nroCampo = strtoull(listaParametros[3], NULL, 0);

	iDescriptorRegistroPtr descRegistro = DescriptorRegistroFactory_Nuevo(listaParametros[2]);
	iFeaturePtr clave = FeatureFactory_Nuevo(descRegistro->ObtenerDescriptorCampo(0), listaParametros[4], NULL);
	descRegistro->Dispose();

	iRegistroPtr registro = NULL;

	iVpTree_ABMPtr vpTree = VpTree_ABMFactory_Nuevo(listaParametros[0], nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16);
	eResultadoVpTree_ABM resultado = vpTree->Buscar(clave, &registro);

	if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Inexistente)
		fprintf(salida, "ERROR!! No existe un registro con esa clave.\n");
	else if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok)
	{
		if (registro)
			for (size_t i = 0; i < registro->ObtenerCantidadCampos(); i++)
			{
				iFeaturePtr campo = registro->GetFeature(i);

				if (campo->ObtenerTipo() & Mascara_Numero)
				{
					if (campo->ObtenerTipo() & Mascara_Flotante)
						if (campo->ObtenerTipo() & Mascara_64Bits)
							fprintf(salida, "%d", campo->AsNumber().flotante.flotante64);
						else
							fprintf(salida, "%d", campo->AsNumber().flotante.flotante32);
					else
						if (campo->ObtenerTipo() & Mascara_Signo)
							fprintf(salida, "%i", campo->AsNumber().entero.enteroConSigno.entero32ConSigno);
						else
							fprintf(salida, "%u", campo->AsNumber().entero.enteroSinSigno.entero32SinSigno);
				}
				else
				{
					sCadenaANSI *cadena = campo->AsCadenaANSI();

					// recordemos que las cadenas son pascal, y por ende, no tienen terminador de cadena
					char *punteroCadena = cadena->cadena;
					for (size_t i = 0; i < cadena->largo; i++)
						putc(*punteroCadena++, salida);
				}

				fprintf(salida, ",");
			}
	}
	
	if (registro)
		registro->Dispose();
	
	if (clave)
		clave->Dispose();
	
	vpTree->Dispose();
}
