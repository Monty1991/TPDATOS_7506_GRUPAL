CC = g++ 
CXXFLAGS = -std=c++14 -g
ModuloIO = Archivo.o ArchivoFactory.o Bitacora.o BitacoraFactory.o ArchivoBloque.o ArchivoBloqueFactory.o
Utils = RegistroBase.o RegistroBaseFactory.o StringUtils.o
TDA =
SYSTEM = Sistema.o TraceEntry.o TraceEntryFactory.o StackTrace.o StackTraceFactory.o Entorno.o EntornoFactory.o
EXCEPTIONS = Exception.o ExceptionFactory.o
OBJS = $(ModuloIO) $(Utils) $(TDA) $(SYSTEM) $(EXCEPTIONS)
APLICACION = Aplicacion.o
CarpetaFuentes =./Fuentes/
EXEC = TPDatosGrupal.exe

.PHONY: all
all: clean build

.PHONY: build
build: $(EXEC)

Archivo.o: $(CarpetaFuentes)io/Archivo/Fuentes/Archivo.cpp
	$(CC) $(CXXFLAGS) -c $<

ArchivoFactory.o: $(CarpetaFuentes)io/Archivo/Fuentes/ArchivoFactory.cpp Archivo.o
	$(CC) $(CXXFLAGS) -c $<

Bitacora.o: $(CarpetaFuentes)io/Bitacora/Fuentes/Bitacora.cpp ArchivoFactory.o StringUtils.o Exception.o
	$(CC) $(CXXFLAGS) -c $<

BitacoraFactory.o: $(CarpetaFuentes)io/Bitacora/Fuentes/BitacoraFactory.cpp Bitacora.o
	$(CC) $(CXXFLAGS) -c $<

ArchivoBloque.o: $(CarpetaFuentes)io/ArchivoBloque/Fuentes/ArchivoBloque.cpp ArchivoFactory.o
	$(CC) $(CXXFLAGS) -c $<

ArchivoBloqueFactory.o: $(CarpetaFuentes)io/ArchivoBloque/Fuentes/ArchivoBloqueFactory.cpp ArchivoBloque.o
	$(CC) $(CXXFLAGS) -c $<

RegistroBase.o: $(CarpetaFuentes)Utils/RegistroBase/Fuentes/RegistroBase.cpp
	$(CC) $(CXXFLAGS) -c $<

RegistroBaseFactory.o: $(CarpetaFuentes)Utils/RegistroBase/Fuentes/RegistroBaseFactory.cpp RegistroBase.o
	$(CC) $(CXXFLAGS) -c $<

Exception.o: $(CarpetaFuentes)Exceptions/Fuentes/Exception.cpp StringUtils.o
	$(CC) $(CXXFLAGS) -c $<

ExceptionFactory.o: $(CarpetaFuentes)Exceptions/Fuentes/ExceptionFactory.cpp Exception.o
	$(CC) $(CXXFLAGS) -c $<

Sistema.o: $(CarpetaFuentes)Sistema/Fuentes/Sistema.cpp Entorno.o
	$(CC) $(CXXFLAGS) -c $<

TraceEntry.o: $(CarpetaFuentes)Sistema/TraceEntry/Fuentes/TraceEntry.cpp StringUtils.o
	$(CC) $(CXXFLAGS) -c $<

TraceEntryFactory.o: $(CarpetaFuentes)Sistema/TraceEntry/Fuentes/TraceEntryFactory.cpp TraceEntry.o
	$(CC) $(CXXFLAGS) -c $<

StackTrace.o: $(CarpetaFuentes)Sistema/StackTrace/Fuentes/StackTrace.cpp TraceEntryFactory.o
	$(CC) $(CXXFLAGS) -c $<

StackTraceFactory.o: $(CarpetaFuentes)Sistema/StackTrace/Fuentes/StackTraceFactory.cpp StackTrace.o
	$(CC) $(CXXFLAGS) -c $<

StringUtils.o: $(CarpetaFuentes)Utils/StringUtils/Fuentes/StringUtils.cpp
	$(CC) $(CXXFLAGS) -c $<

Aplicacion.o: $(CarpetaFuentes)Aplicacion/Fuentes/Aplicacion.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -c $<

Entorno.o: $(CarpetaFuentes)Sistema/Entorno/Fuentes/Entorno.cpp Bitacora.o StackTraceFactory.o
	$(CC) $(CXXFLAGS) -c $<

EntornoFactory.o: $(CarpetaFuentes)Sistema/Entorno/Fuentes/EntornoFactory.cpp Entorno.o
	$(CC) $(CXXFLAGS) -c $<

$(EXEC): $(CarpetaFuentes)main.cpp  $(APLICACION)
	$(CC) $(CXXFLAGS) $(OBJS) $(APLICACION) $< -o $(EXEC)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(APLICACION) $(EXEC)
