///
/// movement.hpp
/// Define todo os metodos de controle da ponte-H, possibilitando o movimento do carrinho
///


#ifndef MOVEMENT_HH
#define MOVEMENT_HH

#include "internals.hpp"

enum class MovementType : uint8_t {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
}

struct MovementNode {
  MovementType type;
  uint16_t amount;
}

namespace movement_queue {
  namespace constants {
    // Define a quantidade maxima de comandos de condução.
    inline constexpr size_t MAX_MOVEMENT_QUEUE_SIZE = 64;
  }

  static size_t queue_it{};
  static size_t queue_size{};
  static MovementNode queue[constants::MAX_MOVEMENT_QUEUE_SIZE] = {0};

  // @brief Retorna a quantidade total de comandos na fila.
  auto
  size( ) -> size_t {
    return queue_size;
  }

  // @brief Retorna o iterador da fila.
  auto
  iterator( ) -> size_t {
    return queue_it;
  }

  // @brief Retorna verdadeiro se chegamos ao final da fila.
  auto
  empty( ) -> size_t {
    return queue_it >= queue_size;
  }

  // @brief Retorna o comando atual.
  auto
  top( ) -> MovementNode {
    return queue[queue_it];
  }

  // @brief Rertorna o comando atual e passa para o proximo.
  auto
  get_and_consume( ) -> MovementNode {
    if (queue_it >= queue_size) {
      Serial.println("[ERRO] Impossivel percorrer a fila visto que chegamos ao final da fila.");
      return;
    }

    return queue[queue_it++];
  }

  // @brief Reinicia a fila.
  auto
  reset( ) -> void {
    queue_it = 0;
    queue_size = 0;
  }

  // @brief Insere um novo comando a fila.
  // @param node O novo comando
  auto
  insert(MovementNode node) -> void {
    if (queue_size >= constants::MAX_MOVEMENT_QUEUE_SIZE) {
      Serial.println("[ERRO] Impossivel inserir mais um comando visto que a fila de comandos esta cheia.");
      return;
    }

    queue[queue_size++] = node;
  }

  // @brief Adiciona um novo comando de movimento para frente.
  // @param cm A distância em centímetros
  auto
  add_forward(uint16_t cm) -> void {
    insert(MovementNode { .type = MovementType::FORWARD, .value = cm });
  }

  // @brief Adiciona um novo comando de movimento para trás.
  // @param cm A distância em centímetros
  auto
  add_backward(uint16_t cm) -> void {
    insert(MovementNode { .type = MovementType::BACKWARD, .value = cm });
  }

  // @brief Adiciona um novo comando de rotação para esquerda.
  auto
  add_turn_left( ) -> void {
    insert(MovementNode { .type = MovementType::LEFT, .value = 90 });
  }

  // @brief Adiciona um novo comando de rotação para direita.
  auto
  add_turn_right( ) -> void {
    insert(MovementNode { .type = MovementType::RIGHT, .value = 90 });
  }
}

namespace movement {
  namespace constants {
    // Define a velocidade maxima e minima, em intervalo 0 a 255, do carrinho.
    // Este valor condiz com ~6V e 0V de saída.
    inline constexpr uint16_t MAX_SPEED = 75;
    inline constexpr uint16_t MIN_SPEED = 0;
  } // namespace constants

  // @brief Para todo o movimento do carrinho.
  auto
  halt( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MIN_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MIN_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, LOW);
    digitalWrite(internals::pins::L298N_IN3, LOW);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  // @brief Faz o carrinho andar para frente.
  auto
  move_forwards( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, HIGH);
    digitalWrite(internals::pins::L298N_IN2, LOW);
    digitalWrite(internals::pins::L298N_IN3, HIGH);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  // @brief Faz o carrinho andar para trás.
  auto
  move_backwards( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, HIGH);
    digitalWrite(internals::pins::L298N_IN3, LOW);
    digitalWrite(internals::pins::L298N_IN4, HIGH);
  }

  // @brief Faz o carrinho virar para direita.
  auto
  turn_right( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, HIGH);
    digitalWrite(internals::pins::L298N_IN3, HIGH);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  // @brief Faz o carrinho virar para esquerda.
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
