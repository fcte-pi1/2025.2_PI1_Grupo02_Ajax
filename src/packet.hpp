///
/// packet.hpp
/// Estrutura de dados para os pacotes de comunicação TCP.
///

#ifndef PACKET_HH
#define PACKET_HH

#include <cstdint>

#define LOWER_BYTE (0xFF)
#define HIGHER_BYTE (0xFF00)

enum PacketType_t : uint8_t {
  HANDSHAKE = 1,
  MOVE = 2,
  TURN = 3,
  WAIT = 4
};

template<size_t S = 0>
class Packet_t {
public:
  using DataArray_t = uint8_t[S + 1];

public:
  explicit Packet_t(PacketType_t type) {
    type_ = type;
    data_[0] = static_cast<uint8_t>(type);
  }

  explicit Packet_t(PacketType_t type, DataArray_t data) {
    type_ = type;
    data_[0] = static_cast<uint8_t>(type);

    for (size_t i = 1; i < S + 1; ++i)
      data_[i] = data[i - 1];
  }

  [[nodiscard]] size_t size() const noexcept {
    return S + 1;
  }

  [[nodiscard]] PacketType_t type() const noexcept {
    return type_;
  }

  [[nodiscard]] DataArray_t const& data() const noexcept {
    return data_;
  }

  private:
  PacketType_t type_;
  DataArray_t data_;
};

namespace packet_builder {
  /// @brief Cria um novo pacote de handshake.
  /// @returns O pacote
  auto create_handshake( ) -> Packet_t<> {
    return Packet_t<>( PacketType_t::HANDSHAKE );
  }

  /// @brief Cria um novo pacote de espera.
  /// @returns O pacote
  auto create_wait( ) -> Packet_t<> {
    return Packet_t<>( PacketType_t::WAIT );
  }

  /// @brief Cria um novo pacote de movimento linear.
  /// @param distance_cm A Distância em centímetros.
  /// @returns O pacote
  auto create_move( uint16_t distance_cm ) -> Packet_t<2> {
    uint8_t lower = (distance_cm & HIGHER_BYTE) >> 8;
    uint8_t higher = distance_cm & LOWER_BYTE;

    // Formatação litte-endian.
    uint8_t data[] = { lower, higher };

    return Packet_t<2>( PacketType_t::WAIT, data );
  }
}

#endif
