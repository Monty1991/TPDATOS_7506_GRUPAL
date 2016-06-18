#include "../Headers/NumberUtils.h"
#include "../../../Exceptions/ExceptionFactory.h"

size_t TablaTamanioPorTipo[] = {1, 2, 4, 8};

size_t NumberUtils_CalcularEspacioSerializacion(eValueType tipo)
{
	if (!(tipo & Mascara_Numero))
		Throw("InvalidArgumentTypeException", "Tipo numerico invalido");

	return TablaTamanioPorTipo[tipo & 3];
}

size_t NumberUtils_Serializar(char *buff, uNumber numero, eValueType tipo)
{
	size_t size = 0;
	Sistema_Execute(size = NumberUtils_CalcularEspacioSerializacion(tipo););

	switch (size)
	{
		case 1:
		{
			if (tipo & Mascara_Signo)
			{
				INT8 value = numero.entero.enteroConSigno.entero8ConSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
			else
			{
				unsigned INT8 value = numero.entero.enteroSinSigno.entero8SinSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
		}
		break;

		case 2:
		{
			if (tipo & Mascara_Signo)
			{
				INT16 value = numero.entero.enteroConSigno.entero16ConSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
			else
			{
				unsigned INT16 value = numero.entero.enteroSinSigno.entero16SinSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
		}
		break;

		case 4:
		{
			if (tipo & Mascara_Signo)
			{
				INT32 value = numero.entero.enteroConSigno.entero32ConSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
			else
			{
				unsigned INT32 value = numero.entero.enteroSinSigno.entero32SinSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
		}
		break;

		case 8:
		{	if (tipo & Mascara_Signo)
			{
				INT64 value = numero.entero.enteroConSigno.entero64ConSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
			else
			{
				unsigned INT64 value = numero.entero.enteroSinSigno.entero64SinSigno;
				for (size_t i = size; i > 0; i--)
					*buff++ = value >> ((i - 1) * 8);
			}
		}
		break;
	}

	return size;
}

size_t NumberUtils_Hidratar(const char *buff, uNumber *numero, eValueType tipo)
{
	size_t size;

	Sistema_Execute(size = NumberUtils_CalcularEspacioSerializacion(tipo););

	switch (size)
	{
		case 1:
		{
			if (tipo & Mascara_Signo)
			{
				INT8 value;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroConSigno.entero8ConSigno = value;
			}
			else
			{
				unsigned INT8 value;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroSinSigno.entero8SinSigno = value;
			}		
		}
		break;

		case 2:
		{
			if (tipo & Mascara_Signo)
			{
				INT16 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroConSigno.entero16ConSigno = value;
			}
			else
			{
				unsigned INT16 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroSinSigno.entero16SinSigno = value;
			}					
		}
		break;

		case 4:
		{
			if (tipo & Mascara_Signo)
			{
				INT32 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroConSigno.entero32ConSigno = value;
			}
			else
			{
				unsigned INT32 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroSinSigno.entero32SinSigno = value;
			}			
		}
		break;

		case 8:
		{
			if (tipo & Mascara_Signo)
			{
				INT64 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroConSigno.entero64ConSigno = value;
			}
			else
			{
				unsigned INT64 value = 0;

				for (size_t i = 0; i < size; i++)
				{
					value = value << 8;
					unsigned char x = *buff++;
					value |= x;
				}

				numero->entero.enteroSinSigno.entero64SinSigno = value;
			}			
		}
		break;
	}

	return size;
}
