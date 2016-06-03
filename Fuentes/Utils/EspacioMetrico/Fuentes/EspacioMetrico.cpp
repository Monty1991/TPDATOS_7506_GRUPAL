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

float EspacioMetrico::CalcularDistancia(sCadenaANSI *clave1, sCadenaANSI *clave2)
{
	sCadenaANSI *coord11, *coord12, *coord21, *coord22;

	this->SepararCoordenadas(clave1, &coord11, &coord12);
	this->SepararCoordenadas(clave2, &coord21, &coord22);

	size_t X = this->DistanciaLevenshtein(coord11, coord21);
	size_t Y = this->DistanciaLevenshtein(coord12, coord22);

	// limpiamos
	delete[] coord11->cadena;
	delete[] coord12->cadena;
	delete[] coord21->cadena;
	delete[] coord22->cadena;
	delete coord11;
	delete coord12;
	delete coord21;
	delete coord22;

	return sqrt(X*X + Y*Y);
}

size_t EspacioMetrico::CalcularPivote(size_t *listaClaves, size_t cantidadClaves)
{
	// Para cada componente de min, se asigna el menor valor del componente correspondiente de todas las claves
	size_t minCoordX = (size_t)(-1ull), minCoordY = (size_t)(-1ull);

	for (size_t i = 0; i < cantidadClaves; i++)
	{
		size_t coordX, coordY;

		this->SepararCoordenadas(listaClaves[i], &coordX, &coordY);
		if (coordX < minCoordX)
			minCoordX = coordX;

		if (coordY < minCoordY)
			minCoordY = coordY;
	}

	return this->JuntarCoordenadas(minCoordX, minCoordY);
}

sCadenaANSI *EspacioMetrico::CalcularPivote(sCadenaANSI **listaClaves, size_t cantidadClaves)
{
	// Para cada componente de min, se asigna la cadena de menor long del componente correspondiente de todas las claves

	sCadenaANSI *pivote;
	sCadenaANSI *minCoord1 = NULL, *minCoord2 = NULL;

	for (size_t i = 0; i < cantidadClaves; i++)
	{
		sCadenaANSI *coord1, *coord2;
		this->SepararCoordenadas(listaClaves[i], &coord1, &coord2);
		
		if (!minCoord1)
			minCoord1 = coord1;
		else
		{
			if (coord1->largo < minCoord1->largo)
			{
				delete[] minCoord1->cadena;
				delete minCoord1;
				minCoord1 = coord1;
			}
		}

		if (!minCoord2)
			minCoord2 = coord2;
		else
		{
			if (coord2->largo < minCoord2->largo)
			{
				delete[] minCoord2->cadena;
				delete minCoord2;
				minCoord2 = coord2;
			}
		}

		if (minCoord1 != coord1)
		{
			delete [] coord1->cadena;
			delete coord1;
		}

		if (minCoord2 != coord2)
		{
			delete [] coord2->cadena;
			delete coord2;
		}
	}
	
	pivote = this->JuntarCoordenadas(minCoord1, minCoord2);

	if (minCoord1)
	{
		delete[] minCoord1->cadena;
		delete minCoord1;
	}

	if (minCoord2)
	{
		delete[] minCoord2->cadena;
		delete minCoord2;
	}

	return pivote;
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

void EspacioMetrico::SepararCoordenadas(sCadenaANSI *clave, sCadenaANSI **coord1, sCadenaANSI **coord2)
{
	sCadenaANSI *X = new sCadenaANSI();
	X->largo = clave->largo / 2 + (clave->largo % 2);
	X->cadena = new char[X->largo];

	sCadenaANSI *Y = new sCadenaANSI();
	Y->largo = clave->largo / 2;
	Y->cadena = new char[Y->largo];

	for (size_t i = 0; i < clave->largo; i++)
	{
		if (i % 2)
			Y->cadena[i / 2] = clave->cadena[i];
		else
			X->cadena[i / 2] = clave->cadena[i];
	}

	*coord1 = X;
	*coord2 = Y;
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

// solo funciona correctamente si 0 <= long(coord1) - long(coord2) <= 1
// en otras palablas, si todas las claves son de la misma long
sCadenaANSI *EspacioMetrico::JuntarCoordenadas(sCadenaANSI *coord1, sCadenaANSI *coord2)
{
	sCadenaANSI *clave = new sCadenaANSI();
	clave->largo = coord1->largo + coord2->largo;
	clave->cadena = new char[clave->largo];

	for (size_t i = 0; i < clave->largo; i++)
		clave->cadena[i] = (i % 2 ? coord2->cadena[i / 2]: coord1->cadena[i / 2]);

	return clave;
}

size_t EspacioMetrico::DistanciaLevenshtein(sCadenaANSI *coord1, sCadenaANSI *coord2)
{
	// por las dudas
	if (!coord1->largo)
		return coord2->largo;
	if (!coord2->largo)
		return coord1->largo;

	size_t oldRow[coord1->largo + 1];
	size_t actualRow[coord1->largo + 1];

	for (size_t i = 0; i < coord1->largo + 1; i++)
		oldRow[i] = i;

	for (size_t fila = 0; fila < coord2->largo; fila++)
	{
		actualRow[0] = fila;
		for (size_t columna = 1; columna < coord1->largo + 1; columna++)
		{
			size_t costoSustitucion = oldRow[columna - 1];
			if (coord1->cadena[columna - 1] == coord2->cadena[fila])
			{
				actualRow[columna] = costoSustitucion;
				continue;
			}

			size_t costoBorrado = oldRow[columna];
			size_t costoInsercion = actualRow[columna - 1];

			size_t minCosto = (costoInsercion < costoBorrado? costoInsercion : costoBorrado);
			minCosto = (minCosto < costoSustitucion? minCosto : costoSustitucion);
			
			actualRow[columna] = minCosto + 1;
		}

		// avanzamos una fila
		for (size_t columna = 0; columna < coord1->largo + 1; columna++)
			oldRow[columna] = actualRow[columna];
	}

	// He aqui la respuesta :)
	return actualRow[coord1->largo];
}
