from enum import Enum


class PacketType(Enum):
    NONE = b"\x00"
    HANDSHAKE = b"\x01"
    MOVE = b"\x02"
    TURN = b"\x03"
    STATUS = b"\x04"

    @staticmethod
    def from_number(n: int):
        for m in PacketType:
            if m.to_number() == n:
                return m

        return PacketType.NONE

    def to_number(self):
        return int.from_bytes(self.value)


class Packet:
    def __init__(self, type: PacketType, data: bytes | None) -> None:
        """Cria um novo pacote de qualquer tipo, com qualquer dados"""
        self.type = type
        self.data = bytes(b"".join([type.value, data or bytes()]))

    @staticmethod
    def from_bytes(data: bytes):
        return Packet(PacketType.from_number(data[0]), data[1:])

    @staticmethod
    def handshake():
        """Cria um novo pacote de handshake"""
        return Packet(PacketType.HANDSHAKE, None)

    @staticmethod
    def move(cm: int):
        """Cria um novo pacote de movimento, em centímetros"""
        return Packet(PacketType.MOVE, cm.to_bytes(2, "little"))

    @staticmethod
    def turn(deg: int):
        """Cria um novo pacote de rotação, em graus"""
        return Packet(PacketType.MOVE, deg.to_bytes(2, "little"))
