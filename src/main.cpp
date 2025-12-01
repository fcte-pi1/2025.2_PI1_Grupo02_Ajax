#include "connection.hpp"
#include "buzzer.hpp"
#include "internals.hpp"
#include "accsensor.hpp"
#include "movement.hpp"
#include <cstdlib>

void setup() {
  // Inicializa comunicação serial e configura pinos de GPIO.
  internals::initialize_serial();
  internals::initialize_pins();
  //accsensor::setupmpu();
                         
  //start melody:
  buzzer::run_buzzer_melody1(buzzer::melody1, buzzer::noteDurations1);
  //accsensor::setupmpu(); //already verifies if mpu exists!
  // Inicializa ponto de acesso WIFI.
  while (!internals::initialize_wifi())
    delay(1000);
  
}

void run_queue_test(){
  // Tentamos conectar ao cliente.
  if (!connection::attempt_connection()) {
    delay(1000);
    return;
  }

  // Realiza a conexão com o cliente.
  connection::handle_connection();

  // Executa os movimentos.
  movement::run();
}
