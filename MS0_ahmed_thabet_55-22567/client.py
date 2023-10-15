import socket
import select
import sys
#initiate Client socket with the TCP connection
client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
# binding the client socket with the localhost as ip and port number
port=22567
# try to connect to the server with associated port and id
client_socket.connect(('127.0.0.1',port)) #'127.0.0.1' is the localhost in ipv4␣↪format
# open a connection until sending CLOSE SOCKET
while True:
    message=input("enter your message: ")
    #client_socket.send(message.encode())
    if(message == "CLOSE SOCKET"):
        client_socket.close()
        break
        
    else:
        client_socket.send(bytes(message.encode()))
        client_message = client_socket.recv(1024).decode()
        
        
        print("Server response:", client_message)
# send message as bytes
#recieve respose if existh