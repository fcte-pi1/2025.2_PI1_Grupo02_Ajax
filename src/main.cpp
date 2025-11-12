#include "connection.hpp"
#include "internals.hpp"
#include "accsensor.hpp"
#include "movement.hpp"

void setup() {
  // Inicializa comunicação serial e configura pinos de GPIO.
  internals::initialize_serial();
  internals::initialize_pins();

  // accsensor::setupmpu();

  // Inicializa ponto de acesso WIFI.
  while (!internals::initialize_wifi())
    delay(1000);
}

void loop() {
  // Tentamos conectar ao cliente.
  if (!connection::attempt_connection()) {
    delay(1000);
    return;
  }

  // Realiza a conexão com o cliente.
  connection::handle_connection();
  
  // if(accsensor::mpu.begin()){
  //   accsensor::readsensor_toserial();
  // }

  // movement::run( );

  movement::move_forward( );
  delay(5000);
  movement::halt( );
  delay(5000);
}
