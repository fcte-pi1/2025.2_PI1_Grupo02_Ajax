import socket
import time
from packet_type import Packet, PacketType

HOST = "192.168.4.1"
PORT = 8080

if __name__ == "__main__":
    # Criação da conexão TCP
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Conexão com a ESP32
    sock.connect((HOST, PORT))

    initialized = False

    while not initialized:
        handshake = sock.recv(1024)

        if handshake[0] == PacketType.HANDSHAKE.to_number():
            sock.send(Packet.handshake().data)
            initialized = True
