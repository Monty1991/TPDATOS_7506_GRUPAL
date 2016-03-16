#include "../Headers/Archivo.h"
#include <stdarg.h>

Archivo::Archivo(const char *nombre)
{
	this->file = fopen(nombre, "r+b");
}

Archivo::~Archivo()
{
	if (!this->file)
		return;

	this->Flush();
	fclose(this->file);
}

void Archivo::Read(char *buff, int amount)
{
	fread(buff, sizeof(char), amount, this->file);
}

void Archivo::Write(char *buff, int amount)
{
	fwrite(buff, sizeof(char), amount, this->file);
}

void Archivo::Seek(int position)
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
