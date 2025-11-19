#include "connection.hpp"
#include "internals.hpp"
#include "accsensor.hpp"
#include "movement.hpp"
#include <cstdlib>

void setup() {
  // Inicializa comunicação serial e configura pinos de GPIO.
  internals::initialize_serial();
  internals::initialize_pins();
  accsensor::setupmpu(); //already verifies if mpu exists!
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
  
  
  int bias{20};
  // movement::run( );
  for(int i = 0; i < 10; i++){
    accsensor::mpu.getEvent(&a, &g, &temp);
    if(std::abs(g.giro.z) > .01){
      bias *= g.gyro.z;
      movement::move_forwards(bias);
    }
    movement::move_forwards();
    delay(50);
  }
  movement::halt( );
  delay(5000);
}
