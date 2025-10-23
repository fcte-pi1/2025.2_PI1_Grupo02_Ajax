#include "internals.hpp"
#include "connection.hpp"

void setup() {
  // Inicializa comunicação serial e configura pinos de GPIO.
  internals::initialize_serial( );
  internals::initialize_pins( );

  // Inicializa ponto de acesso WIFI.
  while ( !internals::initialize_wifi( ) )
    delay(1000);
}

void loop() {
    // Tentamos conectar ao cliente.
    if ( !connection::attempt_connection( ) ) {
        delay(1000);
        return;
    }

    delay(100);
}
