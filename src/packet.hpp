///
/// packet.hpp
/// Estrutura de dados para os pacotes de comunicação TCP.
///

#ifndef PACKET_HH
#define PACKET_HH

enum PacketType_t : unsigned char {
  HANDSHAKE = 0x1
};

template<size_t S = 2>
class Packet_t {
public:
  using DataArray_t = unsigned char[S];

public:
  explicit Packet_t(PacketType_t type, DataArray_t data) {
    type_ = type;

    for (size_t i = 0; i < S; ++i)
      data_[i] = data[i];
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

public:
  static Packet_t<1> handshake() {
    unsigned char bytes[] = { 0x1 };

    return Packet_t<1>( PacketType_t::HANDSHAKE, bytes );
  }

private:
  PacketType_t type_;
  DataArray_t data_;
};

#endif
