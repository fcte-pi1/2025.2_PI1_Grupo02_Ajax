///
/// movement.hpp
/// Define todo os metodos de controle da ponte-H, possibilitando o movimento do carrinho
///


#ifndef MOVEMENT_HH
#define MOVEMENT_HH

#include "internals.hpp"

namespace movement {
  namespace constants {
    // Define a velocidade maxima e minima, em intervalo 0 a 255, do carrinho.
    // Este valor condiz com ~6V e 0V de saída.
    inline constexpr uint16_t MAX_SPEED = 75;
    inline constexpr uint16_t MIN_SPEED = 0;
  } // namespace constants

  auto
  halt( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MIN_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MIN_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, LOW);
    digitalWrite(internals::pins::L298N_IN3, LOW);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  auto
  move_forwards( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, HIGH);
    digitalWrite(internals::pins::L298N_IN2, LOW);
    digitalWrite(internals::pins::L298N_IN3, HIGH);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  auto
  move_backwards( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, HIGH);
    digitalWrite(internals::pins::L298N_IN3, LOW);
    digitalWrite(internals::pins::L298N_IN4, HIGH);
  }

  auto
  turn_right( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, HIGH);
    digitalWrite(internals::pins::L298N_IN3, HIGH);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  auto
  turn_left( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, HIGH);
    digitalWrite(internals::pins::L298N_IN2, LOW);
    digitalWrite(internals::pins::L298N_IN3, LOW);
    digitalWrite(internals::pins::L298N_IN4, HIGH);
  }
} // namespace movement

#endif
