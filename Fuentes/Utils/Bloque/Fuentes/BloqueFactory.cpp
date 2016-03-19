#include "../BloqueFactory.h"
#include "../Headers/Bloque.h"

iBloquePtr BloqueFactory_Nuevo(const char *buffer, size_t tamanioBloque)
{
	return new Bloque(buffer, tamanioBloque);
}
