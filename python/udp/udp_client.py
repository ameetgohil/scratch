import socket
import sys

UDP_IP_ADDRESS = sys.argv[1]
UDP_PORT_NO = int(sys.argv[2])

with open(sys.argv[3], "rb") as f:
    msg = f.read();

clientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

clientSock.sendto(msg, (UDP_IP_ADDRESS, UDP_PORT_NO))
