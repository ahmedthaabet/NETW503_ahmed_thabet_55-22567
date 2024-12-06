import socket
import select
import sys

client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
port=4493
client_socket.connect(('172.20.10.2',port)) 
while True:
    message=input("enter your message: ")
    client_socket.send(bytes(message.encode()))
    messageClient = client_socket.recv(1024)
    messageClientDecoded = messageClient.decode()
    if(message == "CLOSE SOCKET"):
        client_socket.close()
        exit()
    print("Server response:", messageClientDecoded)

