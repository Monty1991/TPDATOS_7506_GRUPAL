#include "../MapaDeBitsFactory.h"
#include "../Headers/MapaDeBits.h"

iMapaDeBitsPtr MapaDeBitsFactory_Nuevo(iBloquePtr bloque)
{
	return new MapaDeBits(bloque);
}
