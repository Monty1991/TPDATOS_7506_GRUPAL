#include "../ArchivoFactory.h"
#include "../Headers/Archivo.h"

const char *TablaTiposArchivos[] = 
{
	"r+b",	// eTipoArchivo_Binario
	"r+",	// eTipoArchivo_Texto
	"a+"	// eTipoArchivo_Log
};

iArchivoPtr ArchivoFactory_Nuevo(const char *nombre, eTipoArchivo tipoArchivo)
{
	
	return new Archivo(nombre, TablaTiposArchivos[tipoArchivo]);
}
