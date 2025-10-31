import socket
import time

HOST = '192.168.4.1'
PORT = 8080

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

sending = False

while True:
    if not sending:
        data = sock.recv(1024)
        print(data.hex())

        if data[0] == 0x1:
            sock.send(data)
            sending = True
    else:
        #data = sock.recv(1024)
        #sock.send(bytes(b"\x01\x02\x03\x3f"))

        sock.send(bytes(b"\x02\x00\xFF"))
        print('Enviando movimento')
        time.sleep(0.5)
        sock.send(bytes(b"\x03\x03\xFF"))
        print('Enviando rotacao')
        time.sleep(0.5)

    
