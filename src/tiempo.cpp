#include "tiempo.hpp"
#include <chrono>

// Usamos un "alias para no escribir nombres tan largos y complicados"
using Reloj = std::chrono::high_resolution_clock;

Tiempo::Tiempo() {
  // Al nacer, el reloj debe estar en cero
  resetear();
}

void Tiempo::marcarInicio() {
  // Capturamos el instante exacto de "ahora"
  puntoInicio = Reloj::now();
}

void Tiempo::marcarFin() {
  // Capturamos el final
  auto puntoFin = Reloj::now();

  // Calculamos la diferencia entre Fin e Inicio
  // Usamos nanosegundos para mas precisión.
  auto duracion =
std::chrono::duration_cast<std::chrono::nanoseconds>(puntoFin - puntoInicio);

  // Lo sumamos al acumulador (el cuentaKilómetros)
  totalNanosegundos += duracion.count();
}

long long Tiempo::obtenerNanosegundos() const {
  return totalNanosegundos;
}

void Tiempo::resetear() {
  totalNanosegundos = 0;
}