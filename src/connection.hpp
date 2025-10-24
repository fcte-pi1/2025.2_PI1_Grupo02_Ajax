///
/// connection.hpp
/// Realiza a comunicação entre o microcontrolador e o dispositivo externo.
///

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "internals.hpp"
#include "packet.hpp"

enum ConnectionState_t {
  UNINITIALIZED = 0,
  WAITING_CONNECTION = 1,
  WAITING_HANDSHAKE = 2,
  CONNECTED = 3,
};

namespace connection {
  namespace constants {
    // Tamanho máximo de cada pacote.
    static constexpr size_t MAX_BUFFER_SIZE = 256;
  }

  static ConnectionState_t state = UNINITIALIZED;

  WiFiServer server(8080);
  WiFiClient client;

  /// @brief Tenta conectar-se ao cliente.
  /// @returns Se a conexão foi feita com sucesso.
  inline
  auto attempt_connection( ) -> bool {
    // Checamos se o servidor ainda não foi inicializado.
    if ( state == UNINITIALIZED ) {
      state = WAITING_CONNECTION;

      server.begin();
      server.setNoDelay(true);
    }

    bool is_connected = client.connected();

    // Se não estamos conectados, vamos tentar uma conexão.
    if ( !is_connected ) {
      if ( ( client = server.available() ) ) {
        state = WAITING_HANDSHAKE;

        Serial.println("[INFO] Possivel cliente conectado, enviando handshake.");
      }

      else if ( state != WAITING_CONNECTION ) {
        state = WAITING_CONNECTION;

        Serial.println("[INFO] Cliente desconectado, pronto para reconexao.");
      }
    }

    digitalWrite(internals::pins::LED_BUILTIN,
      static_cast<uint8_t>(is_connected));

    return is_connected;
  }

  /// @brief Lida com os pacotes recebidos do back-end.
  auto receive_packets( ) -> void {
    // Vemos se temos bytes a serem lidos.
    if ( !client.available() ) {
      return;
    }

    // Checamos se estamos esperando o handshake do backend.
    if ( state == WAITING_HANDSHAKE ) {
      char type = client.read();

      // Se o pacote recebido começa com 0x01, isso significa que recebemos o handshake de volta.
      if ( type == static_cast<uint8_t>(PacketType_t::HANDSHAKE) ) {
        Serial.println("[INFO] Handshake recebido, cliente conectado com sucesso!");

        // Confirmada conexão.
        state = CONNECTED;
      }
    }

    else if ( state == CONNECTED ) {
      char buffer[constants::MAX_BUFFER_SIZE];

      size_t packet_size = client.readBytesUntil(0x3f, buffer, constants::MAX_BUFFER_SIZE);

      Serial.print("[INFO] Recebido pacote: ");
      for (size_t i = 0; i < packet_size; ++i)
        Serial.printf(" %x\n", buffer[i]);
    }
  }

  /// @brief Lida com os pacotes sendo enviados ao back-end.
  auto send_packets( ) -> void {
    // Checamos se temos que enviar o handshake pro backend.
    if ( state == WAITING_HANDSHAKE ) {
      // Criamos um novo pacote de handshake.
      static const auto handshake = Packet_t<>( PacketType_t::HANDSHAKE );

      client.write(handshake.data(), handshake.size());
    }
  }

  /// @brief Executa a comunicação bidirecional com o back-end.
  inline
  auto handle_connection( ) -> void {
    receive_packets( );
    send_packets( );
  }
}

#endif
