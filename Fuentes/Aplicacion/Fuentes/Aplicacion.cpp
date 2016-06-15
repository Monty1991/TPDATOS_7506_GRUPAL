#include "../Headers/Aplicacion.h"
#include "../../Exceptions/Headers/iException.h"
#include "../../Sistema/Sistema/Headers/Sistema.h"
#include "../../Comandos/Comando/ComandoFactory.h"

#include <stdio.h>
#include <string.h>

Aplicacion::Aplicacion()
{
	
}

Aplicacion::~Aplicacion()
{
	
}

int Aplicacion::main(int argc, const char **argv)
{
	int result = 0;
	
	TryCatchBlock(
	{
		if (argc < 2)
		{
			fprintf(stdout, "ERROR!! No se indico un comando\n");
			result = 1;
			return result;
		}
		
		iComandoPtr comando = ComandoFactory_Nuevo(argv[1]);
		
		if (!comando)
		{
			fprintf(stdout, "%s no se reconoce como un comando valido\n", argv[1]);
			result = 1;
			return result;
		}

		// quitamos el nombre de la aplicacion y del comando
		Sistema_Execute(comando->Ejecutar(stdout, argv + 2, argc - 2););

		comando->Dispose();
		
		result = 0;
	},
	[&](iExceptionPtr e){
		Sistema_Log(e);
		e->Dispose();
		return 1;
	})
	
	return result;
}
