#include "../HidratadorNumericoFactory.h"
#include "../Headers/HidratadorNumerico.h"

iHidratadorNumericoPtr HidratadorNumericoFactory_Nuevo()
{
	return new HidratadorNumerico();
}
