#include "../Headers/EspacioMetrico.h"
#include <math.h>

EspacioMetrico::EspacioMetrico(): Object()
{
}

EspacioMetrico::~EspacioMetrico()
{
}

iEspacioMetrico *EspacioMetrico::Copiar()
{
	Object::IncrementarContador();
	return this;
}

iEspacioMetrico *EspacioMetrico::Clone()
{
	return new EspacioMetrico();
}

void EspacioMetrico::Dispose()
{
	Object::Dispose();
}

float EspacioMetrico::CalcularDistancia(size_t clave1, size_t clave2)
{
	size_t coord11, coord12, coord21, coord22;
	this->SepararCoordenadas(clave1, &coord11, &coord12);
	this->SepararCoordenadas(clave2, &coord21, &coord22);

	size_t X, Y;
	
	// Como son numeros sin signo, importa el orden
	// para evitar valores incorrectos
	if (coord11 > coord21)
		X = coord11 - coord21;
	else
		X = coord21 - coord11;

	if (coord12 > coord22)
		Y = coord12 - coord22;
	else
		Y = coord22 - coord12;

	// Devolvemos la norma euclideana
	return sqrt(X*X + Y*Y);
}

size_t EspacioMetrico::CalcularPivote(size_t *listaClaves, size_t cantidadClaves)
{
	// El hipercubo se delimita con los vectores min y max
	// Para cada componente de min, se asigna el menor valor del componente correspondiente a todas las claves
	// Para cada componente de max, se asigna el mayor valor del componente correspondiente a todas las claves
	// Y el pivote es simplemente min.
	size_t minCoordX = (size_t)(-1ull), minCoordY = (size_t)(-1ull), maxCoordX = 0, maxCoordY = 0;

	for (size_t i = 0; i < cantidadClaves; i++)
	{
		size_t coordX, coordY;

		this->SepararCoordenadas(listaClaves[i], &coordX, &coordY);
		if (coordX > maxCoordX)
			maxCoordX = coordX;
		if (coordX < minCoordX)
			minCoordX = coordX;

		if (coordY > maxCoordY)
			maxCoordY = coordY;
		if (coordY < minCoordY)
			minCoordY = coordY;
	}

	return this->JuntarCoordenadas(minCoordX, minCoordY);
}

void EspacioMetrico::SepararCoordenadas(size_t clave, size_t *coord1, size_t *coord2)
{
	unsigned short x = 0;
	unsigned short y = 0;

	for (size_t pos = 0; pos < sizeof(size_t); pos++)
	{
		bool value = clave >> ((sizeof(size_t) -1) - pos);
		if (pos % 2)
		{
			y = y << 1;
			y |= (value & 1);
		}
		else
		{
			x = x << 1;
			x |= (value & 1);
		}
	}

	*coord1 = x;
	*coord2 = y;
}

size_t EspacioMetrico::JuntarCoordenadas(size_t coord1, size_t coord2)
{
	size_t clave = 0;
	for (size_t i = 0; i < (sizeof(size_t) / 2); i++)
	{
		clave |= (coord1 >> (((sizeof(size_t) / 2) - 1) - i)) & 1;
		clave = clave << 1;
		clave |= (coord2 >> (((sizeof(size_t) / 2) - 1) - i)) & 1;
		clave = clave << 1;
	}
	return clave;
}
