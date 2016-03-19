#include "../Headers/Aplicacion.h"
#include "../../Exceptions/Headers/iException.h"
#include "../../Sistema/Sistema/Headers/Sistema.h"
#include "../../Utils/RegistroBase/RegistroBaseFactory.h"
#include "../../io/ArchivoBloque/ArchivoBloqueFactory.h"

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

			iBloquePtr bloque = archivoBloque->LeerBloque(0);			// cargamos el mapa de bits
			char buff[2049];
			memset(buff, 0, 2048);										// lo inicializamos en 0
			try
			{
				Sistema_Execute( bloque->EscribirBloque(buff, 0, 2048););	// actualizamos el bloque
				archivoBloque->EscribirBloque(0, bloque);					// actualizamos el mapa de bits
				buff[0] = 1;												// seteamos el bit 0 del mapa
				Sistema_Execute( bloque->EscribirBloque(buff, 0, 1););		// actualizamos el bloque
				archivoBloque->EscribirBloque(0, bloque);					// actualizamos el archivo
			}
			catch (iExceptionPtr e)
			{
				Sistema_ObtenerEntorno()->ObtenerBitacora()->Log(e);
				e->Dispose();
			}

			bloque->Dispose();									// no lo necesitamos mas
	
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
