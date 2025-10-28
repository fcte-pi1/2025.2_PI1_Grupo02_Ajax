///
/// internals.hpp
/// Encapsula toda a configuração de periféricos e GPIOs internas ao
/// microcontrolador
///

#ifndef INTERNALS_HH
#define INTERNALS_HH

#include <Arduino.h>
#include <WiFi.h>

namespace internals {
namespace pins {
// LED acoplado ao microcontrolador.
static constexpr uint8_t LED_BUILTIN = 2u;
} // namespace pins

namespace constants {
// Taxa de comunicação UART serial.
static constexpr unsigned long BAUD_RATE = 115200u;

// Nome da rede de WIFI roteada pelo microcontrolador.
static constexpr const char *SSID = "ESP Network";

// Senha da rede de WIFI roteada pelo microcontrolador.
static constexpr const char *PASSWORD = "87654321";

// O endereço de IP estático do microcontrolador.
static const IPAddress STATIC_IP_ADDR(192, 168, 4, 1);

// O gateway da rede WIFI do microcontrolador.
static const IPAddress GATEWAY(255, 255, 255, 0);
} // namespace constants

/// @brief Configura todos os pinos de GPIO utilizados pela ESP32.
inline auto initialize_pins() -> void {
  Serial.println("[INFO] Configurando pinos.");
  pinMode(pins::LED_BUILTIN, OUTPUT);
}

/// @brief Configura a comunicação UART serial para monitoramento.
inline auto initialize_serial() -> void {
  Serial.begin(constants::BAUD_RATE);
  delay(1000);
  Serial.println(
      "[INFO] Comunicacao UART inicializada com baud rate de 115200.");
}

/// @brief Configura o ponto de acesso de WIFI roteado pela ESP32.
/// @return Se a configuração funcionou ou não.
inline auto initialize_wifi() -> bool {
  if (!WiFi.softAPConfig(constants::STATIC_IP_ADDR, constants::STATIC_IP_ADDR,
                         constants::GATEWAY)) {
    Serial.println("[ERRO] Incapaz de configurar o ponto de acesso.");
    return false;
  }

  if (!WiFi.softAP(constants::SSID, constants::PASSWORD)) {
    Serial.println("[ERRO] Incapaz de inicializar o ponto de acesso.");
    return false;
  }

  Serial.println("[INFO] Ponto de acesso criado com sucesso");
  Serial.print("[INFO] IP estatico: ");
  Serial.println(WiFi.softAPIP());
  return true;
}
} // namespace internals

#endif
