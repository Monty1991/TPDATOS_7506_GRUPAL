#include "../ContenedorRegistroFactory.h"
#include "../Headers/ContenedorRegistro.h"

iContenedorRegistroPtr ContenedorRegistroFactory_Nuevo(iRegistroPtr *listaRegistros, size_t cantidadRegistros)
{
	return new ContenedorRegistro(listaRegistros, cantidadRegistros);
}
