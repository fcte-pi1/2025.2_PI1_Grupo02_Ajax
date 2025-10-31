import socket
import select
import time
from packet import Packet, PacketType

# IP e porta da ESP32
HOST = "192.168.4.1"
PORT = 8080


def split_packets(data: bytes) -> list[bytes]:
    if len(data) % 3 != 0:
        return []

    list = []
    for i in range(0, len(data), 3):
        list[i] = data[i : i + 3]

    return list


def receive_packets():
    # Recebemos dados brutos da ESP32, vamos dividi-los em pacotes.
    data = sock.recv(1024)
    packets = split_packets(data)

    # Garantimos que temos pacotes para ler, caso contrário, temos pacotes inválidos
    if len(packets) < 0:
        print(f"Recebidos {len(data)} bytes invalidos")
        return

    print(f"Recebido {len(packets)} pacotes")

    # Iteramos para cada pacote
    for packet in packets:
        packet = Packet.from_bytes(data)

        if packet.type == PacketType.NONE:
            print("Recebido pacote invalido")

        print(f"Tipo: {packet.type}, dados: {packet.data.decode()}")


def send_packets():
    # Criamos dois pacotes e enviamo-os.
    move_150 = Packet.move(150)
    turn_90 = Packet.turn(90)

    sock.send(move_150.data)
    sock.send(turn_90.data)


if __name__ == "__main__":
    # Criação da conexão TCP
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Conexão com a ESP32
    sock.connect((HOST, PORT))

    received_handshake = False

    # Esperando o handshake da ESP32 para efetuarmos a conexão.
    while not received_handshake:
        handshake = sock.recv(1024)

        # Enviamos o handshake de volta.
        if handshake[0] == PacketType.HANDSHAKE.to_number():
            sock.send(Packet.handshake().data)
            received_handshake = True

    while True:
        # Checamos se temos pacotes a receber.
        incoming, _, _ = select.select([sock], [], [], 0.1)

        data_available = len(incoming) > 0

        # Se sim, lemos os pacotes.
        if data_available:
            receive_packets()

        # Enviando pacotes agora.
        send_packets()
