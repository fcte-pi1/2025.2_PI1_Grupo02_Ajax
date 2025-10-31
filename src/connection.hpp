///
/// connection.hpp
/// Realiza a comunicação entre o microcontrolador e o dispositivo externo.
///

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "internals.hpp"
#include "packet.hpp"
#include <cstdint>

/// Define o estado da conexão com o back-end.
enum ConnectionState_t {
  UNINITIALIZED = 0,      // Não inicializado
  WAITING_CONNECTION = 1, // Esperando back-end se conectar
  WAITING_HANDSHAKE = 2,  // Esperando validação do back-end
  CONNECTED = 3,          // Conectado com back-end
};

/// Define o estado da comunicação com o back-end, especificando
/// os pacotes que devem ser esperados e enviados.
enum CommunicationState_t {
  NONE = -1,                // Desconectado
  WAITING_FOR_COMMANDS = 0, // Esperando os comandos de condução do back-end
  RUNNING = 1, // Executando comandos de condução e enviando dados de telemetria
  END = 2      // Terminado a execução do movimento
};

namespace connection {
namespace constants {
// Tamanho máximo de cada pacote.
static constexpr size_t MAX_BUFFER_SIZE = 32;
} // namespace constants

// Estados atuais da máquina de comunicação.
static ConnectionState_t connection_state = UNINITIALIZED;
static CommunicationState_t communication_state = NONE;

WiFiServer server(8080);
WiFiClient client;

/// @brief Tenta conectar-se ao cliente.
/// @returns Se a conexão foi feita com sucesso.
inline auto attempt_connection() -> bool {
  // Checamos se o servidor ainda não foi inicializado.
  if (connection_state == UNINITIALIZED) {
    connection_state = WAITING_CONNECTION;

    server.begin();
    server.setNoDelay(true);
  }

  bool is_connected = client.connected();

  // Se não estamos conectados, vamos tentar uma conexão.
  if (!is_connected) {
    if ((client = server.available())) {
      connection_state = WAITING_HANDSHAKE;

      Serial.println("[INFO] Possivel cliente conectado, enviando handshake.");
    }

    else if (connection_state != WAITING_CONNECTION) {
      connection_state = WAITING_CONNECTION;
      communication_state = NONE;

      Serial.println("[INFO] Cliente desconectado, pronto para reconexao.");
    }
  }

  digitalWrite(internals::pins::LED_BUILTIN,
               static_cast<uint8_t>(is_connected));

  return is_connected;
}

/// @brief Lida com os pacotes recebidos do back-end.
auto receive_packets() -> void {
  // Vemos se temos bytes a serem lidos.
  if (!client.available()) {
    return;
  }

  // Checamos se estamos esperando o handshake do backend.
  if (connection_state == WAITING_HANDSHAKE) {
    char type = client.read();

    // Se o pacote recebido começa com 0x01, isso significa que recebemos o
    // handshake de volta.
    if (type == static_cast<uint8_t>(PacketType_t::HANDSHAKE)) {
      Serial.println(
          "[INFO] Handshake recebido, cliente conectado com sucesso!");

      // Confirmada conexão.
      connection_state = CONNECTED;
      communication_state = WAITING_FOR_COMMANDS;

      // Limpamos a entrada.
      client.flush();
    }
  }

  else if (connection_state == CONNECTED) {
    char buffer[constants::MAX_BUFFER_SIZE];

    // Todos os pacotes, exceto o handshake, possuem 3 bytes.
    size_t packet_size = client.readBytes(buffer, 3);

    Serial.printf("[INFO] Recebido pacote de %d bytes.\n", packet_size);

    switch (buffer[0]) {
    case PacketType_t::MOVE:
      Serial.printf("[PACKET] Movimento: %dcm\n", (buffer[1] << 8) + buffer[2]);
      break;

    case PacketType_t::TURN:
      Serial.printf("[PACKET] Rotacao: %ddeg\n", (buffer[1] << 8) + buffer[2]);
      break;

    default:
      Serial.println("[PACKET] Pacote nao reconhecido recebido!");
      break;
    }
  }
}

/// @brief Lida com os pacotes sendo enviados ao back-end.
auto send_packets() -> void {
  // Checamos se temos que enviar o handshake pro backend.
  if (connection_state == WAITING_HANDSHAKE) {
    // Criamos um novo pacote de handshake.
    static const auto handshake = packet_builder::create_handshake();

    client.write(handshake.data(), handshake.size());
  }

  else if (connection_state == CONNECTED) {
    const auto status = packet_builder::create_status(connection_state);

    client.write(status.data(), status.size());
  }
}

/// @brief Executa a comunicação bidirecional com o back-end.
inline auto handle_connection() -> void {
  receive_packets();
  send_packets();
}
} // namespace connection

#endif
