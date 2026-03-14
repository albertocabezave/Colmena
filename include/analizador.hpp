#ifndef ANALIZADOR_HPP
#define ANALIZADOR_HPP

#include <vector>
#include <string> // Para soportar frases.
#include <cstddef> // Para usar size_t

class Analizador {
  public:
    // Constructor: Recibe frase completa.
    Analizador(std::string objetivo);

    // La función estrella: El Calco.
    // Analiza el buffer y cuenta cuantas coincidencias encontra.
    // Recibe el buffer y el tamaño REAL de datos útiles.
    void analizarBloque(const std::vector<char>& buffer, size_t bytesUtiles);

    // Devuelve el total de coincidencias encontradas hasta el momento
    long long obtenerTotalCoincidencias() const;

    // Reinicia el contador para un nuevo análisis.
    void resetear();

  private:
    std::string objetivoBusqueda; // Aquí se guarda lo que el usuario eligió buscar.
    long long coincidenciasEncontradas;
    size_t indiceProgreso; // NUeva variable para no perder la frase entre bloques
};

#endif