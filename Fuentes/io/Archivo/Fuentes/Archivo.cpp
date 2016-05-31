#include "../Headers/Archivo.h"
#include <stdarg.h>

Archivo::Archivo(const char *nombre, const char *mode)
{
	this->file = fopen(nombre, "a+");
	freopen(nombre, mode, this->file);
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

void Archivo::Write(const char *buff, size_t count)
{
	fwrite(buff, sizeof(char), count, this->file);
}

void Archivo::Seek(size_t position)
{
	fseek(this->file, position, SEEK_SET);
}

fpos_t Archivo::GetFileSize()
{
	fseek(this->file, 0, SEEK_END);
	fpos_t fpos;
	fgetpos(this->file, &fpos);
	return fpos;
}

int Archivo::ReadChar()
{
	return getc(this->file);
}

void Archivo::WriteChar(int c)
{
	putc(c, this->file);
}

void Archivo::Printf(const char *format)
{
	fprintf(this->file, "%s", format);
}

void Archivo::Flush()
{
	fflush(this->file);
}

void Archivo::Close()
{
	delete this;
}
