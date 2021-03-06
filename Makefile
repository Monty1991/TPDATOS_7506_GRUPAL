CC = g++
CXXFLAGS = -std=c++11 -g -Wall
MODULOIO = Archivo.o ArchivoFactory.o Bitacora.o BitacoraFactory.o ArchivoBloque.o ArchivoBloqueFactory.o ArchivoArbol.o ArchivoArbolFactory.o
UTILS = StringUtils.o NumberUtils.o Bloque.o BloqueFactory.o MapaDeBits.o MapaDeBitsFactory.o NodoFactory.o NodoArbolPuntoOptimo.o NodoArbolPuntoOptimoFactory.o EspacioMetrico.o
MEMORY = Object.o DescriptorRegistro.o DescriptorRegistroFactory.o Feature.o FeatureFactory.o Registro.o RegistroFactory.o ContenedorRegistro.o ContenedorRegistroFactory.o
TDA = LinkedList.o LinkedListFactory.o Heap.o HeapFactory.o VpTree_ABM.o VpTree_ABMFactory.o
SYSTEM = Sistema.o TraceEntry.o TraceEntryFactory.o StackTrace.o StackTraceFactory.o Entorno.o EntornoFactory.o
EXCEPTIONS = Exception.o ExceptionFactory.o
SERIALIZADORES = SerializadorNodoFactory.o SerializadorNodoArbolPuntoOptimo.o SerializadorNodoArbolPuntoOptimoFactory.o
HIDRATADORES = HidratadorNodoFactory.o HidratadorNodoArbolPuntoOptimo.o HidratadorNodoArbolPuntoOptimoFactory.o
COMANDOS = ComandoAlta.o ComandoAltaFactory.o ComandoBuscar.o ComandoBuscarFactory.o ComandoBaja.o ComandoBajaFactory.o ComandoModificacion.o ComandoModificacionFactory.o ComandoFactory.o ComandoCarga.o ComandoCargaFactory.o
OBJS = $(MODULOIO) $(MEMORY) $(TDA) $(UTILS) $(SERIALIZADORES) $(HIDRATADORES) $(SYSTEM) $(EXCEPTIONS) $(COMANDOS)
APLICACION = Aplicacion.o
CarpetaFuentes =./Fuentes/
OBJDIR = Objects
EXEC = TPDatosGrupal

.PHONY: all
all: build

.PHONY: build
build: | $(OBJDIR) $(EXEC)

$(OBJDIR):
	mkdir $(OBJDIR)

.SECONDEXPANSION:
$(MODULOIO): $$(join $(CarpetaFuentes)io/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

.SECONDEXPANSION:
$(MEMORY): $$(join $(CarpetaFuentes)Memoria/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

.SECONDEXPANSION:
$(TDA): $$(join $(CarpetaFuentes)TDA/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

.SECONDEXPANSION:
$(UTILS): $$(join $(CarpetaFuentes)Utils/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

.SECONDEXPANSION:
$(SERIALIZADORES): $$(join $(CarpetaFuentes)Serializadores/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

.SECONDEXPANSION:
$(HIDRATADORES): $$(join $(CarpetaFuentes)Hidratadores/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

.SECONDEXPANSION:
$(COMANDOS): $$(join $(CarpetaFuentes)Comandos/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

.SECONDEXPANSION:
$(SYSTEM): $$(join $(CarpetaFuentes)Sistema/, $$(subst Factory,,$$(subst .o,, $$@))/Fuentes/$$(subst .o,,$$@).cpp)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

$(EXCEPTIONS): %.o: $(CarpetaFuentes)Exceptions/Fuentes/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

$(APLICACION): $(CarpetaFuentes)Aplicacion/Fuentes/Aplicacion.cpp $(OBJS)
	$(CC) $(CXXFLAGS) -c $< -o $(OBJDIR)/$@

$(EXEC): $(CarpetaFuentes)main.cpp $(APLICACION)
	$(CC) $(CXXFLAGS) $(addprefix $(OBJDIR)/, $(OBJS) $(APLICACION)) $< -o $(EXEC)

.PHONY: clean
clean:
	-rm -f $(OBJDIR)/*.o $(EXEC)

