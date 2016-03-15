CC = g++
CXXFLAGS = -std=c++11
OBJS =
CarpetaFuentes =./Fuentes/
EXEC = TPDatosGrupal.exe

.PHONY: all
all: clean build

.PHONY: build
build: $(EXEC)

$(EXEC): $(CarpetaFuentes)main.cpp  $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $< -o $(EXEC)

.PHONY: clean
clean:
	-rm -f $(EXEC)
