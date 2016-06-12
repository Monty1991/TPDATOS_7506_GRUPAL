#include <stdlib.h>

#include "../Headers/ComandoAlta.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"
#include "../../../Memoria/Registro/RegistroFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Memoria/DescriptorRegistro/DescriptorRegistroFactory.h"

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
		fprintf(salida, "ERROR!! Se esperaban al menos 5 parametros\n");
		return;
	}

	size_t tamanioBloque = strtoull(listaParametros[1], NULL, 0);
	size_t nroCampo = strtoull(listaParametros[3], NULL, 0);
	iVpTree_ABMPtr vpTree = VpTree_ABMFactory_Nuevo(listaParametros[0], nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16);

	iDescriptorRegistroPtr descRegistro = DescriptorRegistroFactory_Nuevo(listaParametros[2]);
	if (!descRegistro)
	{
		fprintf(salida, "ERROR!! El formato del descriptor de registro provisto no es valido\n");
		return;
	}
	
	/*
	Si, el codigo es asqueroso, pero pongo la primer version aqui
	 */
	
	const char *cadenaRegistro;
	iRegistroPtr registro = RegistroFactory_Nuevo(descRegistro->ObtenerCantidadCampos());
	for (size_t i = 0; i < registro->ObtenerCantidadCampos(); i++)
	{
		switch (descRegistro->ObtenerDescriptorCampo(i)->desc)
		{
			case eDescriptorCampo::eDescriptorCampo_U:
			{
				uValue value;
				value.primitivo.numero.entero.enteroSinSigno.entero32SinSigno = strtoul(cadenaRegistro, (char **)&cadenaRegistro, 0);
				iFeaturePtr campo = FeatureFactory_Nuevo(value, eValueType::eValueType_U4);
				registro->SetFeature(i, campo);
			}
			break;

			case eDescriptorCampo::eDescriptorCampo_I:
			{
				uValue value;
				value.primitivo.numero.entero.enteroConSigno.entero32ConSigno = strtol(cadenaRegistro, (char **)&cadenaRegistro, 0);
				iFeaturePtr campo = FeatureFactory_Nuevo(value, eValueType::eValueType_I4);
				registro->SetFeature(i, campo);
			}
			break;

			case eDescriptorCampo::eDescriptorCampo_F:
			{
				uValue value;
				value.primitivo.numero.flotante.flotante32 = strtod(cadenaRegistro, (char **)&cadenaRegistro);
				iFeaturePtr campo = FeatureFactory_Nuevo(value, eValueType::eValueType_F32);
				registro->SetFeature(i, campo);
			}
			break;

			case eDescriptorCampo::eDescriptorCampo_C:
			{
				sCadenaANSI cadenaANSI;
				cadenaANSI.cadena = (char *)cadenaRegistro;
				
				size_t largoCadena = 0;
				while ((cadenaRegistro[largoCadena] != ',') && (cadenaRegistro[largoCadena] != '\0'))
					largoCadena++;
				
				cadenaANSI.largo = largoCadena;

				// El registro se queda con la referencia, por eso no hay Dispose
				iFeaturePtr campo = FeatureFactory_Nuevo(&cadenaANSI);
				registro->SetFeature(i, campo);			
			}
			break;

			case eDescriptorCampo::eDescriptorCampo_CV:
			{
				sCadenaANSI cadenaANSI;
				cadenaANSI.cadena = (char *)cadenaRegistro;
				
				size_t largoCadena = 0;
				while ((cadenaRegistro[largoCadena] != ',') && (cadenaRegistro[largoCadena] != '\0'))
					largoCadena++;
				
				cadenaANSI.largo = largoCadena;

				// El registro se queda con la referencia, por eso no hay Dispose
				iFeaturePtr campo = FeatureFactory_Nuevo(&cadenaANSI);
				registro->SetFeature(i, campo);			
			}
			break;
		}

		// llegados aquí, se leyo hasta la coma
		cadenaRegistro++;
	}
	
	eResultadoVpTree_ABM resultado = vpTree->Alta(registro, true);
	if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok)
		fprintf(salida, "La operacion se ha completado con exito\n");
	else if(resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Duplicado)
		fprintf(salida, "ERROR!! Ya existe un registro con esa clave. Tal vez queria modificar?\n");

	vpTree->Dispose();
}
