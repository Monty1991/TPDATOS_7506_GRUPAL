#include <stdio.h>
#include "Utils/RegistroBase/RegistroBaseFactory.h"
#include "Exceptions/Exception.h"
#include "Sistema/Sistema.h"
#include "Utils/StringUtils/Headers/StringUtils.h"
#include "Aplicacion/Headers/Aplicacion.h"

int main(int argc, char **argv)
{
	Sistema_Inicializar();
	
//	printf("Hola, mundo\n");
//	printf("Chau, mundo\n");
	
	Aplicacion *aplicacion = new Aplicacion();
	
	int i = 0;
	Sistema_EnterFunction(
		{ i = aplicacion->main(argc, argv);}
	);

	Sistema_Finalizar();
	return i;
}
