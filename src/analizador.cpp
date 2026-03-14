#include "analizador.hpp"

// Constructor: Usamos una Lista de inicialización
// (:variable(valor))
// Esta es la forma más rapida en C++ de asignar valores al nacer.
Analizador::Analizador(std::string objetivo)
  : objetivoBusqueda(objetivo), coincidenciasEncontradas(0), indiceProgreso(0) {
}

void Analizador::analizarBloque(const std::vector<char>& buffer,
  size_t bytesUtiles) {

   // Si la frase está vacía, no hay nada que buscar.
   if (objetivoBusqueda.empty()) return;

   // Guardamos el tamaño de la frase para evitar llamadas repetidas a length()
   const size_t tamanoFrase = objetivoBusqueda.length();

   // EL CALCO: Recorremos solo los bytes que el Lector nos dijo
   // que eran válidos.
   for (size_t i = 0; i < bytesUtiles; ++i) {
    // Comparamos el byte actual buffer[i] con el caracter que toca
    // segun nuestro progreso en la frase.
    if (buffer[i] == objetivoBusqueda[indiceProgreso]) {
      indiceProgreso++;

      // Si el progreso alcanza el tamaño de la frase es una
      // coincidencia completa.
      if (indiceProgreso == tamanoFrase) {
        coincidenciasEncontradas++;
        indiceProgreso = 0; // Reiniciamos para buscar la siguiente frase
      }
    } else {
      // Si fallamos, revisamos si el byte actual es por lo menos
      // el inicio de la frase
      if (buffer[i] == objetivoBusqueda[0]) {
        indiceProgreso = 1;
      } else {
        indiceProgreso = 0;
      }
    }
   }
}

long long Analizador::obtenerTotalCoincidencias() const {
  return coincidenciasEncontradas;
}

void Analizador::resetear() {
  coincidenciasEncontradas = 0;
  indiceProgreso = 0; // También reiniciamos el progreso de la frase.
}