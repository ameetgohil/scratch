import socket
import sys

UDP_IP_ADDRESS = sys.argv[1]
UDP_PORT_NO = int(sys.argv[2])

serverSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

serverSock.bind((UDP_IP_ADDRESS, UDP_PORT_NO))

while True:
    data, addr = serverSock.recvfrom(1024)
    print("Message", data)
