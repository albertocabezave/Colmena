#ifndef LECTOR_HPP
#define LECTOR_HPP

#include <string>
#include <fstream>
#include <vector>

class Lector {
  public:
    // Constructor: Inicializa el estado del lector
    Lector();

    // 1. Acción: Abrir el archivo en modo binario
    // Devuelve true si el archivo se pudo abrir correctamente
    bool abrirArchivo(const std::string& ruta);

    // 2. Acción: Mover datos del DISCO a la RAM (al buffer)
    // Devuelve cuántos bytes se movieron realmente
    size_t leerBloque(std::vector<char>& buffer);

    // 3. Función de Salud: Informa si hubo un fallo físico
    // Devuelve true si ocurrió un error crítico de hardware en la
    // última lectura, y false si se vació el balde.
    bool huboErrorDeHardware() const;

    // 4. Acción: Cerrar la tubería con el disco.
    void cerrar();

  private:
    std::ifstream archivo; // La tubería física.
    const size_t TAMANO_BLOQUE = 65536; // Nuestro balde de 64KB

};

#endif