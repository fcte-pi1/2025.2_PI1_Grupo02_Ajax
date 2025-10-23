#include "internals.hpp"
#include "connection.hpp"

void setup() {
  // Initialize serial communication and GPIO configuration.
  internals::initialize_serial( );
  internals::initialize_pins( );

  // Initialize access point.
  while ( !internals::initialize_wifi( ) )
    delay(1000);
}

void loop() {
    // Try to connect to client.
    if ( !connection::attempt_connection( ) ) {
        delay(1000);
        return;
    }

    delay(100);
}
