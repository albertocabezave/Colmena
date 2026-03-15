#include <iostream>
#include <vector>
#include <string>
#include "tiempo.hpp"
#include "lector.hpp"
#include "analizador.hpp"

int main() {
  // 1. Configuración inicial
  std::string ruta;
  std::string objetivo;

  std::cout << "--| COLMENA | --\n-- Procesador de logs\n By Alberto Cabeza 2026 --" <<
  std::endl;
  std::cout << "Introduce la Ruta del Archivo: ";
  std::cin >> ruta;

  // Limpiamos el buffer de entrada para que getline no lea el ENTER anterior.
  std::cin.ignore();

  std::cout << "Introduce la Frase o el Caracter a buscar: ";
  std::getline(std::cin, objetivo); // Usamos getline para capturar espacios.

  // 2. Nacimiento de los componentes.
  Lector lector;
  Analizador analizador(objetivo);
  Tiempo cronometro;

  // Creamos el balde de 64KB (655536)
  std::vector<char> balde(65536);

  // 3. Intento de apertura
  if (!lector.abrirArchivo(ruta)) {
    std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
    return 1;
  }

  cronometro.marcarInicio();
  // 4. EL BUCLE PRINCIPAL
  size_t bytesLeidos = 0;
  long long totalBytesProcesados = 0; // Nueva variable para la velocidad

  // Mientras el lector tenga datos (mas de 0 bytes)...
  while ((bytesLeidos = lector.leerBloque(balde)) > 0) {
    totalBytesProcesados += bytesLeidos; // Sumamos lo que vamos leyendo.


    // El Analizador solo procesa lo que el Lector trajo de verdad
    analizador.analizarBloque(balde, bytesLeidos);
  }
  cronometro.marcarFin();

  // 5. Verificación de salud.
  if (lector.huboErrorDeHardware()) {
    std::cerr << "\nALERTA: El análisis se detuvo por un fallo en el disco." <<
    std::endl;
  } else {
    // 6. Reporte Final
    double tiempoSegundos = cronometro.obtenerNanosegundos() / 1.0e9;
    double tamanoMB = totalBytesProcesados / (1024.0 * 1024.0);
    // Evitamos división por cero y calculamos velocidad.
    double velocidad = (tiempoSegundos > 0.000001) ? (tamanoMB / tiempoSegundos) : 0;

    std::cout << "\n [ -- Reporte de rendimiento --]" << std::endl;
    std::cout << "Datos Procesados: " << tamanoMB << " MB" << std::endl;
    std::cout << "Coincidencias: " << analizador.obtenerTotalCoincidencias() <<
    std::endl;

    // Si el tiempo es menos de 1 segundo, mostrar ms, sino, segundos.
    if (tiempoSegundos < 1.0) {
      std::cout << "Tiempo: " << (tiempoSegundos * 1000.0) << " ms" << std::endl;
    } else {
      std::cout << "Tiempo: " << (tiempoSegundos) << " s" << std::endl;
    }
    std::cout << "Velocidad Real: " << velocidad << " MB/s" << std::endl;
  }

  lector.cerrar();
  return 0;
}