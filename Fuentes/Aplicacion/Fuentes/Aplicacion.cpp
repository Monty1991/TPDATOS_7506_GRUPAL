#include "../Headers/Aplicacion.h"
#include "../../Exceptions/Headers/iException.h"
#include "../../Sistema/Sistema/Headers/Sistema.h"
#include "../../Utils/RegistroBase/RegistroBaseFactory.h"
#include "../../io/ArchivoBloque/ArchivoBloqueFactory.h"
#include "../../Utils/MapaDeBits/MapaDeBitsFactory.h"

#include <stdio.h>
#include <string.h>

Aplicacion::Aplicacion()
{
	
}

Aplicacion::~Aplicacion()
{
	
}

int Aplicacion::main(int argc, char **argv)
{
	TryCatchBlock(
	{
		printf("Hola, mundo\n");
		
		iArchivoBloquePtr archivoBloque = ArchivoBloqueFactory_Nuevo("asdf.dat", 2048);

			iBloquePtr bloque = archivoBloque->LeerBloque(0);					// cargamos el mapa de bits
			char buff[2048];
			memset(buff, 0, 2048);
			iMapaDeBitsPtr mapaDeBits = MapaDeBitsFactory_Nuevo(bloque);
			bloque->Dispose();

			try
			{
				Sistema_Execute( mapaDeBits->SetearBit(0, true););
				Sistema_Execute( mapaDeBits->SetearBit(0, false););				// forzamos al mapa de bits a modificarse

				Sistema_Execute( archivoBloque->EscribirBloque(0, mapaDeBits->Leer());); // volcamos el mapa de bits al archivo
				Sistema_Execute( mapaDeBits->SetearBit(5, true););				// volvemos a modificar el mapa
				Sistema_Execute( archivoBloque->EscribirBloque(0, mapaDeBits->Leer()););	// actualizamos el archivo
			}
			catch (iExceptionPtr e)
			{
				Sistema_ObtenerEntorno()->ObtenerBitacora()->Log(e);
				e->Dispose();
			}

			mapaDeBits->Dispose();
			
		archivoBloque->Close();									// cerramos el archivo

		iRegistroBasePtr reg = RegistroBaseFactory_Nuevo(4);
		Sistema_Execute( reg->ObtenerCampo(5); );
		reg->Disponer();

		return 0;
	},
	[&](auto e){
		Sistema_ObtenerEntorno()->ObtenerBitacora()->Log(e);
		e->Dispose();
		return 1;
	})
}
