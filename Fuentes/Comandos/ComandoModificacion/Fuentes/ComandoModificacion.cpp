#include <stdlib.h>

#include "../Headers/ComandoModificacion.h"
#include "../../../TDA/VpTree_ABM/VpTree_ABMFactory.h"
#include "../../../Memoria/Registro/RegistroFactory.h"
#include "../../../Memoria/Feature/FeatureFactory.h"
#include "../../../Memoria/DescriptorRegistro/DescriptorRegistroFactory.h"
#include "../../../Sistema/Sistema/Headers/Sistema.h"

ComandoModificacion::ComandoModificacion()
{

}

ComandoModificacion::~ComandoModificacion()
{

}

void ComandoModificacion::Dispose()
{
	delete this;
}

const char *ComandoModificacion::ObtenerNombre()
{
	return "modificacion";
}

void ComandoModificacion::ImprimirAyuda(FILE *salida)
{
	fprintf(salida, "modificacion: n t s i r\n");
	fprintf(salida, "\tn: nombre archivo de datos\n");
	fprintf(salida, "\tt: tamanio de bloque, en bytes\n");
	fprintf(salida, "\ts: schema de registro, ver documentacion\n");
	fprintf(salida, "\ti: nro de campo que contiene la clave\n");
	fprintf(salida, "\tr: registro, siguiendo el formato del schema\n");
}

void ComandoModificacion::Ejecutar(FILE *salida, const char **listaParametros, size_t cantidad)
{
	if (cantidad < 5)
	{
		fprintf(salida, "ERROR!! Se esperaban al menos 5 parametros.\n");
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

	/*
	Si, el codigo es asqueroso, pero pongo la primer version aqui
	 */
	
	const char *cadenaRegistro = listaParametros[4];
	iRegistroPtr registro = RegistroFactory_Nuevo(descRegistro->ObtenerCantidadCampos());
	for (size_t i = 0; i < registro->ObtenerCantidadCampos(); i++)
	{
		iFeaturePtr campo = NULL;
		switch (descRegistro->ObtenerDescriptorCampo(i)->desc)
		{
			case eDescriptorCampo::eDescriptorCampo_U:
			{
				uValue value;
				value.primitivo.numero.entero.enteroSinSigno.entero32SinSigno = strtoul(cadenaRegistro, (char **)&cadenaRegistro, 0);
				campo = FeatureFactory_Nuevo(value, eValueType::eValueType_U4);
			}
			break;

			case eDescriptorCampo::eDescriptorCampo_I:
			{
				uValue value;
				value.primitivo.numero.entero.enteroConSigno.entero32ConSigno = strtol(cadenaRegistro, (char **)&cadenaRegistro, 0);
				campo = FeatureFactory_Nuevo(value, eValueType::eValueType_I4);
			}
			break;

			case eDescriptorCampo::eDescriptorCampo_F:
			{
				uValue value;
				value.primitivo.numero.flotante.flotante32 = strtod(cadenaRegistro, (char **)&cadenaRegistro);
				campo = FeatureFactory_Nuevo(value, eValueType::eValueType_F32);
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

				campo = FeatureFactory_Nuevo(&cadenaANSI);
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

				campo = FeatureFactory_Nuevo(&cadenaANSI);
			}
			break;
		}

		Sistema_Execute(registro->SetFeature(i, campo););
		campo->Dispose();
		// llegados aquí, se leyo hasta la coma
		cadenaRegistro++;
	}
	descRegistro->Dispose();

	eResultadoVpTree_ABM resultado;

	iVpTree_ABMPtr vpTree = VpTree_ABMFactory_Nuevo(nombreArchivo, nroCampo, tamanioBloque, (tamanioBloque * 3)/10, 16);

	Sistema_Execute(resultado = vpTree->Modificacion(registro););

	if (resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Ok)
		fprintf(salida, "La operacion se ha completado con exito.\n");
	else if(resultado == eResultadoVpTree_ABM::eResultadoVpTree_ABM__Inexistente)
		fprintf(salida, "ERROR!! No existe una version previa del registro.\n");

	registro->Dispose();
	vpTree->Dispose();
}
