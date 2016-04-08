#include "../SerializadorCadenaUNICODEFactory.h"
#include "../Headers/SerializadorCadenaUNICODE.h"

iSerializadorCadenaUNICODEPtr SerializadorCadenaUNICODEFactory_Nuevo()
{
	return new SerializadorCadenaUNICODE();
}
