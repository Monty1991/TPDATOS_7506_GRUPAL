CC = g++ 
CXXFLAGS = -std=c++11
OBJS = Archivo.o ArchivoFactory.o Bitacora.o BitacoraFactory.o ArchivoBloque.o ArchivoBloqueFactory.o
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

Bitacora.o: $(CarpetaFuentes)io/Bitacora/Fuentes/Bitacora.cpp ArchivoFactory.o
	$(CC) $(CXXFLAGS) -c $<

BitacoraFactory.o: $(CarpetaFuentes)io/Bitacora/Fuentes/BitacoraFactory.cpp Bitacora.o
	$(CC) $(CXXFLAGS) -c $<

ArchivoBloque.o: $(CarpetaFuentes)io/ArchivoBloque/Fuentes/ArchivoBloque.cpp ArchivoFactory.o
	$(CC) $(CXXFLAGS) -c $<

ArchivoBloqueFactory.o: $(CarpetaFuentes)io/ArchivoBloque/Fuentes/ArchivoBloqueFactory.cpp ArchivoBloque.o
	$(CC) $(CXXFLAGS) -c $<

$(EXEC): $(CarpetaFuentes)main.cpp  $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $< -o $(EXEC)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(EXEC)
