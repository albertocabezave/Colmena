# Variables para el compilador
CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -march=native -std=c++17 -Iinclude

# Lista de archivos que forman el programa
SOURCES = src/main.cpp src/lector.cpp src/analizador.cpp src/tiempo.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = colmena

# La reglas principales
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Como convertir cada .cpp en un archivo objeto .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar la basura despues de compilar
clean:
	rm -f src/*.o $(TARGET)