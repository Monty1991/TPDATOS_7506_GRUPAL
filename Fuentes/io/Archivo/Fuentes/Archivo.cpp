#include "../Headers/Archivo.h"
#include <stdarg.h>

Archivo::Archivo(const char *nombre, const char *mode)
{
	this->file = fopen(nombre, mode);
}

Archivo::~Archivo()
{
	if (!this->file)
		return;

	this->Flush();
	fclose(this->file);
}

void Archivo::Read(char *buff, size_t count)
{
	fread(buff, sizeof(char), count, this->file);
}

void Archivo::Write(char *buff, size_t count)
{
	fwrite(buff, sizeof(char), count, this->file);
}

void Archivo::Seek(size_t position)
{
	fseek(this->file, position, SEEK_SET);
}

int Archivo::ReadChar()
{
	return getc(this->file);
}

void Archivo::WriteChar(int c)
{
	putc(c, this->file);
}

void Archivo::Printf(const char *format, ...)
{
	va_list ap;
	fprintf(this->file, format, ap);
}

void Archivo::Flush()
{
	fflush(this->file);
}

void Archivo::Close()
{
	delete this;
}
