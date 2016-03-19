#include "../Headers/Aplicacion.h"
#include "../../Exceptions/Headers/iException.h"
#include "../../Sistema/Sistema.h"
#include "../../Utils/RegistroBase/RegistroBaseFactory.h"

#include <stdio.h>

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
