#include "../Headers/SerializadorNumerico.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../../Utils/StringUtils/Headers/StringUtils.h"

SerializadorNumerico::SerializadorNumerico()
{
	
}

SerializadorNumerico::~SerializadorNumerico()
{
	
}

size_t SerializadorNumerico::CalcularEspacio(uNumber numero, eValueType tipo)
{
	// si tipo no tiene la mascara de numero => no es numero => error
	if (!(tipo & Mascara_Numero))
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

	return 1;	// 8 bits
}

size_t SerializadorNumerico::Serializar(char *buff, uNumber numero, eValueType tipo)
{
	size_t size = 0;
	Sistema_Execute(size = this->CalcularEspacio(numero, tipo););

	switch (size)
	{
		case 1:
		{
			if (tipo & Mascara_Signo)
			{
				INT8 value = numero.entero.enteroConSigno.entero8ConSigno;
				*buff++ = value;
			}
			else
			{
				unsigned INT8 value = numero.entero.enteroSinSigno.entero8SinSigno;
				*buff++ = value;
			}
		}
		break;

		case 2:
		{
			if (tipo & Mascara_Signo)
			{
				INT16 value = numero.entero.enteroConSigno.entero16ConSigno;
				*buff++ = value >> 8;
				*buff++ = value;
			}
			else
			{
				unsigned INT16 value = numero.entero.enteroSinSigno.entero16SinSigno;
				*buff++ = value >> 8;
				*buff++ = value;
			}
		}
		break;

		case 4:
		{
			if (tipo & Mascara_Signo)
			{
				INT32 value = numero.entero.enteroConSigno.entero32ConSigno;
				*buff++ = value >> 24;
				*buff++ = value >> 16;
				*buff++ = value >> 8;
				*buff++ = value;
			}
			else
			{
				unsigned INT32 value = numero.entero.enteroSinSigno.entero32SinSigno;
				*buff++ = value >> 24;
				*buff++ = value >> 16;
				*buff++ = value >> 8;
				*buff++ = value;
			}
		}
		break;

		case 8:
		{	if (tipo & Mascara_Signo)
			{
				INT64 value = numero.entero.enteroConSigno.entero64ConSigno;
				*buff++ = value >> 56;
				*buff++ = value >> 48;
				*buff++ = value >> 40;
				*buff++ = value >> 32;
				*buff++ = value >> 24;
				*buff++ = value >> 16;
				*buff++ = value >> 8;
				*buff++ = value;
			}
			else
			{
				unsigned INT64 value = numero.entero.enteroSinSigno.entero64SinSigno;
				*buff++ = value >> 56;
				*buff++ = value >> 48;
				*buff++ = value >> 40;
				*buff++ = value >> 32;
				*buff++ = value >> 24;
				*buff++ = value >> 16;
				*buff++ = value >> 8;
				*buff++ = value;
			}
		}
		break;
	}

	return size;
}

void SerializadorNumerico::Dispose()
{
	delete this;
}
