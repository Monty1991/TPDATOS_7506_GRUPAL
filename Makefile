CC = g++ 
CXXFLAGS = -std=c++14 -g
ModuloIO = Archivo.o ArchivoFactory.o Bitacora.o BitacoraFactory.o ArchivoBloque.o ArchivoBloqueFactory.o
Utils = RegistroBase.o RegistroBaseFactory.o StringUtils.o Bloque.o BloqueFactory.o MapaDeBits.o MapaDeBitsFactory.o DescriptorRegistro.o DescriptorRegistroFactory.o
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

.SECONDEXPANSION:
$(ModuloIO): $$(join $(CarpetaFuentes)io/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $<

.SECONDEXPANSION:
$(Utils): $$(join $(CarpetaFuentes)Utils/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $<

.SECONDEXPANSION:
$(SYSTEM): $$(join $(CarpetaFuentes)Sistema/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $<

$(EXCEPTIONS): %.o: $(CarpetaFuentes)Exceptions/Fuentes/%.cpp
	$(CC) $(CXXFLAGS) -c $<

Aplicacion.o: $(CarpetaFuentes)Aplicacion/Fuentes/Aplicacion.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -c $<

$(EXEC): $(CarpetaFuentes)main.cpp  $(APLICACION)
	$(CC) $(CXXFLAGS) $(OBJS) $(APLICACION) $< -o $(EXEC)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(APLICACION) $(EXEC)
