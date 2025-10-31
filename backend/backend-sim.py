import socket
import select
import time
from packet import Packet, PacketType

# IP e porta da ESP32
HOST = "192.168.4.1"
PORT = 8080


def receive_packets():
    # Recebemos um pacote e fazemos o que quiser com os dados
    data = sock.recv(1024)
    packet = Packet.from_bytes(data)

    print(f"Tipo: {packet.type}, dados: {packet.data.decode()}")


def send_packets():
    # Criamos dois pacotes e enviamo-os.
    move_150 = Packet.move(150)
    turn_90 = Packet.turn(90)

    sock.send(move_150.data)
    time.sleep(0.1)
    sock.send(turn_90.data)
    time.sleep(0.1)


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

        # Se sim, lemos os pacotes.
        if len(incoming) > 0:
            receive_packets()

        # Enviando pacotes agora.
        send_packets()
