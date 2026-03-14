#include "lector.hpp"
#include <iostream>

Lector::Lector() {
  // El constructor por ahora no necesita hacer nada especial
}

bool Lector::abrirArchivo(const std::string& ruta) {
  // Abrimos el archivo:
  // std::ios::binary -> Modo Lectura.
  archivo.open(ruta, std::ios::binary | std::ios::in);

  // Devolvemos true si se abrió, false si no existe o no hay
  // permisos.
  return archivo.is_open();
}

size_t Lector::leerBloque(std::vector<char>& buffer) {
  // Si el archivo no está listo o llegamos al final, devolvemos 0
  if (!archivo.is_open() || archivo.eof()) {
    return 0;
  }

  // El Letor le dice al archivo: "Escribe directamente en la RAM"
  // archivo.read espera un puntero, por eso usamos buffer.data()
  archivo.read(buffer.data(), TAMANO_BLOQUE);

  // // gcount() nos dice cuantos bytes se leyeron de verdad
  return static_cast<size_t>(archivo.gcount());
}

bool Lector::huboErrorDeHardware() const {
  // bad() devuelve true si hubo fallo físico
  // (Disco desconectado, error de lectura)
  return archivo.bad();
}

void Lector::cerrar() {
  if (archivo.is_open()) {
    archivo.close();
  }
}