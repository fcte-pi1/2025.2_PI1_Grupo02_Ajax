from enum import Enum


class PacketType(Enum):
    HANDSHAKE = b"\x01"
    MOVE = b"\x02"
    TURN = b"\x03"
    STATUS = b"\x04"

    def to_number(self):
        return int.from_bytes(self.value)


class Packet:
    def __init__(self, type: PacketType, data: bytes | None) -> None:
        """Cria um novo pacote de qualquer tipo, com qualquer dados"""
        self.data = bytes(b"".join([type.value, data or bytes()]))

    @staticmethod
    def handshake():
        """Cria um novo pacote de handshake"""
        return Packet(PacketType.HANDSHAKE, None)

    @staticmethod
    def move(cm: int):
        """Cria um novo pacote de movimento"""
        return Packet(PacketType.MOVE, cm.to_bytes(2, "little"))
