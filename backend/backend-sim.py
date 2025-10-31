import socket
from packet import Packet, PacketType

HOST = "192.168.4.1"
PORT = 8080

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
