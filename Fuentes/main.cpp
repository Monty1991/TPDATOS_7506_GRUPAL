#include "Sistema/Sistema.h"
#include "Aplicacion/Headers/Aplicacion.h"

int main(int argc, char **argv)
{
	Sistema_Inicializar();
	
	Aplicacion *aplicacion = new Aplicacion();
	
	int i = aplicacion->main(argc, argv);

	Sistema_Finalizar();
	return i;
}
