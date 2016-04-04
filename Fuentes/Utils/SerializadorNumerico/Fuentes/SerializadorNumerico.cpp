#include "../Headers/SerializadorNumerico.h"
#include "../../../Exceptions/ExceptionFactory.h"
#include "../../StringUtils/Headers/StringUtils.h"

SerializadorNumerico::SerializadorNumerico()
{
	
}

SerializadorNumerico::~SerializadorNumerico()
{
	
}

size_t SerializadorNumerico::CalcularEspacio(uNumber numero, eValueType tipo)
{
	switch(tipo)
	{
		case eValueType::eValueType_I1:
			return sizeof(char);

		case eValueType::eValueType_U1:
			return sizeof(unsigned char);

		case eValueType::eValueType_I2:
			return sizeof(short);

		case eValueType::eValueType_U2:
			return sizeof(unsigned short);

		case eValueType::eValueType_I4:
			return sizeof(int);

		case eValueType::eValueType_U4:
			return sizeof(unsigned int);

		case eValueType::eValueType_I8:
			return sizeof(long long);

		case eValueType::eValueType_U8:
			return sizeof(unsigned long long);

		case eValueType::eValueType_F32:
			return sizeof(float);

		case eValueType::eValueType_F64:
			return sizeof(double);
	}
	
	Throw("InvalidArgumentType", "Tipo numerico invalido");
}

size_t SerializadorNumerico::Serializar(char *buff, uNumber numero, eValueType tipo)
{
	switch(tipo)
	{
		case eValueType::eValueType_I1:
		{
			size_t size = sizeof(char);
			char value = numero.entero.enteroConSigno.entero8ConSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_U1:
		{
			size_t size = sizeof(unsigned char);
			unsigned char value = numero.entero.enteroSinSigno.entero8SinSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_I2:
		{
			size_t size = sizeof(short);
			short value = numero.entero.enteroConSigno.entero16ConSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_U2:
		{
			size_t size = sizeof(unsigned short);
			unsigned short value = numero.entero.enteroSinSigno.entero16SinSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_I4:
		{
			size_t size = sizeof(int);
			int value = numero.entero.enteroConSigno.entero32ConSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_U4:
		{
			size_t size = sizeof(unsigned int);
			unsigned int value = numero.entero.enteroSinSigno.entero32SinSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_I8:
		{
			size_t size = sizeof(long long);
			long long value = numero.entero.enteroConSigno.entero64ConSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_U8:
		{
			size_t size = sizeof(unsigned long long);
			unsigned long long value = numero.entero.enteroSinSigno.entero64SinSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_F32:
		{
			size_t size = sizeof(float);
			// para poder usar el shift, necesitamos trabajar con enteros
			// lo que hacemos es trabajar al flotante "como si fuera" entero
			int value = numero.entero.enteroConSigno.entero32ConSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}

		case eValueType::eValueType_F64:
		{
			size_t size = sizeof(double);
			// para poder usar el shift, necesitamos trabajar con enteros
			// lo que hacemos es trabajar al flotante "como si fuera" entero
			long long value = numero.entero.enteroConSigno.entero64ConSigno;
			for (size_t i = 0; i < size; i++)
				*buff++ = ((value >> ((size - 1 - i) *8)) & 255);

			return size;
		}
	}
	
	Throw("InvalidArgumentType", "Tipo numerico invalido");
}

void SerializadorNumerico::Dispose()
{
	delete this;
}
