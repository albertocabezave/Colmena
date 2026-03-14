 // Header Guard. Para que el compilador no cree la clase
 // Tiempo dos veces si otros archivos incluye tiempo.hpp.
#ifndef TIEMPO_HPP
#define TIEMPO_HPP

#include <chrono>

class Tiempo {
  public:
  Tiempo (); // Definición para el compilador.
   void marcarInicio();
   void marcarFin();
   // 64bits para números grandes, 32bits en 2 seg. pasarían a negativos
   // const para que sea solo de lectura y el procesador no tenga que consultar
   // el dato en cada ciclo.
   long long obtenerNanosegundos() const; 
   // Para limpiar el contador cuando se pase de analizar un archivo
   // a otro nuevo. Tener cuidado con esta función.
   void resetear();

  private:
    // El reloj que usa ticks del procesador, el mas preciso.
    std::chrono::high_resolution_clock::time_point puntoInicio;
    std::chrono::high_resolution_clock::time_point puntoFin;
    long long totalNanosegundos = 0;
};

#endif