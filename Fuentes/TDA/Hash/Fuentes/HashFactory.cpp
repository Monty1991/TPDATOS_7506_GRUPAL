#include "../HashFactory.h"
#include "../Headers/Hash.h"

iHashPtr HashFactory_Nuevo()
{
	return new Hash();
}
