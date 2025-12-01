///
/// movement.hpp
/// Define todo os metodos de controle da ponte-H, possibilitando o movimento do carrinho
/// herda mpu para fins de correção
///


#ifndef MOVEMENT_HH
#define MOVEMENT_HH

#include "accsensor.hpp"
#include "internals.hpp"

enum class MovementType : uint8_t {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

struct MovementNode {
  MovementType type;
  uint16_t value;
};

namespace movement_queue {
  namespace constants {
    // Define a quantidade maxima de comandos de condução.
    inline constexpr size_t MAX_MOVEMENT_QUEUE_SIZE = 64;
  }

  static size_t queue_it{};
  static size_t queue_size{};
  static MovementNode queue[constants::MAX_MOVEMENT_QUEUE_SIZE] = {};

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
  top( ) -> MovementNode* {
    if (empty( )) {
      Serial.println("[ERRO] Impossivel pegar o comando atual visto que a fila ta vazia.");
      return NULL;
    }

    return &queue[queue_it];
  }

  // @brief Retorna o comando atual e passa para o proximo.
  auto
  get_and_consume( ) -> MovementNode* {
    if (empty( )) {
      Serial.println("[ERRO] Impossivel percorrer a fila visto que chegamos ao final da fila.");
      return NULL;
    }

    return &queue[queue_it++];
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
    inline constexpr uint16_t GYRO_SPEED_MULTIPLIER = 5;
    inline constexpr uint16_t MIN_SPEED = 0;
  } // namespace constants

  static bool is_ready = false;

  /// @brief Calcula o tempo em milisegundos para o carrinho andar uma quantidade de centímetros.
  /// @param cm A distância em centímetros
  /// @return O tempo em milisegundos
  auto
  cm_to_ms(uint16_t cm) -> float {
    static constexpr float TO_CM_MS = 0.01f * 1000.f;
    static constexpr float REACTION_TIME_ADJUSTMENT = 475.f;

    // @TODO: Calibrar na FGA.
    // Função linear definida a partir de valores experimentais.
    // Distancia x Tempo
    return 2.1 * cm * TO_CM_MS + REACTION_TIME_ADJUSTMENT;
  }

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
  turn_right() -> void {
    //common init
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, HIGH);
    digitalWrite(internals::pins::L298N_IN2, LOW);
    digitalWrite(internals::pins::L298N_IN3, HIGH);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  auto
  turn_left( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, HIGH);
    digitalWrite(internals::pins::L298N_IN3, LOW);
    digitalWrite(internals::pins::L298N_IN4, HIGH);
  }

  auto
  move_backwards( ) -> void {
    analogWrite(internals::pins::L298N_ENA, constants::MAX_SPEED);
    analogWrite(internals::pins::L298N_ENB, constants::MAX_SPEED);
    digitalWrite(internals::pins::L298N_IN1, LOW);
    digitalWrite(internals::pins::L298N_IN2, HIGH);
    digitalWrite(internals::pins::L298N_IN3, HIGH);
    digitalWrite(internals::pins::L298N_IN4, LOW);
  }

  auto
  move_forwards( ) -> void {
    auto left_speed = (accsensor::rotation > 0.f || abs(accsensor::rotation) < 0.1f) 
      ? constants::MAX_SPEED 
      : constants::MAX_SPEED - abs(accsensor::rotation) * constants::GYRO_SPEED_MULTIPLIER;

    auto right_speed = (accsensor::rotation < 0.f || abs(accsensor::rotation) < 0.1f) 
      ? constants::MAX_SPEED 
      : constants::MAX_SPEED - abs(accsensor::rotation) * constants::GYRO_SPEED_MULTIPLIER;

    analogWrite(internals::pins::L298N_ENA, left_speed);
    analogWrite(internals::pins::L298N_ENB, right_speed * 0.9);
    digitalWrite(internals::pins::L298N_IN1, HIGH);
    digitalWrite(internals::pins::L298N_IN2, LOW);
    digitalWrite(internals::pins::L298N_IN3, LOW);
    digitalWrite(internals::pins::L298N_IN4, HIGH);
  }

  auto
  execute(MovementNode* node) -> void {
    unsigned long timer = 0;
    if (node->type == MovementType::FORWARD) {
      while (timer < cm_to_ms(node->value)) {
        unsigned long begin = millis();

        accsensor::read( );

        move_forwards( );
        delay(10);

        unsigned long end = millis();

        timer += end - begin;
        Serial.printf("Timer: %zu\n", timer);
      }
    }
  }

  auto
  run( ) -> void {
    // Checamos se já executamos todos os comandos ou se não temos comandos pendentes.
    if (movement_queue::empty( )) {
      movement_queue::reset( );
      movement::halt( );

      // @TODO: Soltar o ovo.
      if (is_ready) {}

      is_ready = false;
      return;
    }

    // Checamos se o back-end já indicou que podemos começar o trajeto.
    if (!is_ready) {
      return;
    }

    MovementNode* current = movement_queue::get_and_consume( );

    if (current == NULL) {
      // @TODO: Enviar erro para o back-end.
      Serial.println("[ERRO] A fila de comandos retornou um valor invalido!");
      return;
    }

    execute(current);
  } 
} // namespace movement

#endif
