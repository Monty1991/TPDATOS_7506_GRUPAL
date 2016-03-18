#include "../Headers/Aplicacion.h"
#include "../../Exceptions/Exception.h"
#include "../../Sistema/Sistema.h"

#include <stdio.h>

Aplicacion::Aplicacion()
{
	
}

Aplicacion::~Aplicacion()
{
	
}

int Aplicacion::main(int argc, char **argv)
{
	try
	{
		printf("Hola, mundo\n");
		Throw(Exception, "holis");
	}
	catch (Exception *e)
	{
		Sistema_ObtenerBitacora()->Log(e);
		e->Dispose();
		return 1;
	}
	
	return 0;
}
