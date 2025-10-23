///
/// connection.hpp
/// Realiza a comunicação entre o microcontrolador e o dispositivo externo.
///

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "internals.hpp"

namespace connection {
  static boolean is_initialized = false;

  WiFiServer server(8080);
  WiFiClient client;

  /// @brief Tenta conectar-se ao cliente.
  /// @returns Se a conexão foi feita com sucesso.
  inline
  auto attempt_connection( ) -> bool {
    // Checamos se o servidor ainda não foi inicializado.
    if ( !is_initialized ) {
      is_initialized = true;

      server.begin();
      server.setNoDelay(true);
    }

    bool is_connected = client.connected();

    // Se não estamos conectados, vamos tentar uma conexão.
    if ( !is_connected ) {
      if (( client = server.available() )) {
        Serial.println("[INFO] Cliente conectado com sucesso!");
      }
    }

    digitalWrite(internals::pins::LED_BUILTIN,
      static_cast<uint8_t>(is_connected));

    return is_connected;
  }

  inline
  auto handle_connection( ) -> void {
    client.println("Ola!");
  }
}

#endif
