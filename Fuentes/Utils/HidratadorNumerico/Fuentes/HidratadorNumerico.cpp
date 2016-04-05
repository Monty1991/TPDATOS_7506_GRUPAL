#include "../Headers/HidratadorNumerico.h"
#include "../../../Exceptions/ExceptionFactory.h"

HidratadorNumerico::HidratadorNumerico()
{

}

HidratadorNumerico::~HidratadorNumerico()
{

}

size_t HidratadorNumerico::Hidratar(const char *buff, uNumber *numero, eValueType tipo)
{
	size_t size;

	Sistema_Execute(size = this->CalcularEspacio(buff, tipo););

	switch (size)
	{
		case 1:
		{
			if (tipo & Mascara_Signo)
			{
				__int8 value;
				value = *buff++;
				numero->entero.enteroConSigno.entero8ConSigno = value;
			}
			else
			{
				unsigned __int8 value;
				value = *buff++;
				numero->entero.enteroSinSigno.entero8SinSigno = value;
			}		
		}
		break;

		case 2:
		{
			if (tipo & Mascara_Signo)
			{
				__int16 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					value |= *buff++;
				}

				numero->entero.enteroConSigno.entero16ConSigno = value;
			}
			else
			{
				unsigned __int16 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					value |= *buff++;
				}

				numero->entero.enteroSinSigno.entero16SinSigno = value;
			}					
		}
		break;

		case 4:
		{
			if (tipo & Mascara_Signo)
			{
				__int32 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					value |= *buff++;
				}

				numero->entero.enteroConSigno.entero32ConSigno = value;
			}
			else
			{
				unsigned __int32 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					value |= *buff++;
				}

				numero->entero.enteroSinSigno.entero32SinSigno = value;
			}			
		}
		break;

		case 8:
		{
			if (tipo & Mascara_Signo)
			{
				__int64 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					value |= *buff++;
				}

				numero->entero.enteroConSigno.entero64ConSigno = value;
			}
			else
			{
				unsigned __int64 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					value |= *buff++;
				}

				numero->entero.enteroSinSigno.entero64SinSigno = value;
			}			
		}
		break;
	}

	return size;
}

void HidratadorNumerico::Dispose()
{
	delete this;
}

size_t HidratadorNumerico::CalcularEspacio(const char *buff, eValueType tipo)
{
	if (tipo ^ Mascara_Numero)
		Throw("InvalidArgumentTypeException", "Tipo numerico invalido");

	switch(tipo & 3)
	{
		case Mascara_64Bits:
			return 8;

		case Mascara_32Bits:
			return 4;

		case Mascara_16Bits:
			return 2;
	}

	return 1;
}
