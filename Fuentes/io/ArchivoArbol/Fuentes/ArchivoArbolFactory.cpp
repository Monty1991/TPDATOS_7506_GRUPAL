#include "../ArchivoArbolFactory.h"
#include "../Headers/ArchivoArbol.h"

iArchivoArbolPtr ArchivoArbolFactory_Nuevo(const char *_nombreArchivo,
		size_t _tamanioNodo, size_t _cargaMinima, size_t _tolerancia,
		eTipoArbol tipoArbol) {

	return new ArchivoArbol(_nombreArchivo, _tamanioNodo, _cargaMinima,
			_tolerancia, tipoArbol);
}
