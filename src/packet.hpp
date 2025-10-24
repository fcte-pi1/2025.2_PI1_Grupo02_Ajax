///
/// packet.hpp
/// Estrutura de dados para os pacotes de comunicação TCP.
///

#ifndef PACKET_HH
#define PACKET_HH

enum PacketType_t : unsigned char {
  HANDSHAKE = 0x01,
  MOVE = 0x02,
  TURN = 0x03,
  STATUS = 0x04
};

template<size_t S = 0>
class Packet_t {
public:
  using DataArray_t = unsigned char[S + 1];

public:
  explicit Packet_t(PacketType_t type) {
    type_ = type;
    data_[0] = static_cast<unsigned char>(type);
  }

  explicit Packet_t(PacketType_t type, DataArray_t data) {
    type_ = type;
    data_[0] = static_cast<unsigned char>(type);

    for (size_t i = 1; i < S + 1; ++i)
      data_[i] = data[i - 1];
  }

  [[nodiscard]] size_t size() const noexcept {
    return S;
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
  inline
  auto create_handshake( ) -> Packet_t<> {
    return Packet_t<>( PacketType_t::HANDSHAKE );
  }
}

#endif
