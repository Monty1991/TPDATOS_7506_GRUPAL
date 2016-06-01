#include "../EspacioMetricoFactory.h"
#include "../Headers/EspacioMetrico.h"

iEspacioMetricoPtr EspacioMetricoFactory_Nuevo()
{
	return new EspacioMetrico();
}
