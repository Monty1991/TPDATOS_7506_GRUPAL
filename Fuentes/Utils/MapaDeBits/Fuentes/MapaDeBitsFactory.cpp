#include "../MapaDeBitsFactory.h"
#include "../Headers/MapaDeBits.h"

iMapaDeBitsPtr MapaDeBitsFactory_Nuevo(const char *buff, size_t tamanioMapa)
{
	return new MapaDeBits(buff, tamanioMapa);
}
