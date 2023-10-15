import socket
import select
import sys
#initiate server socket with the TCP connection
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
# binding the server socket with the localhost as ip and port number
port=22567
server_socket.bind(('127.0.0.1',port)) # '127.0.0.1' is the localhost in ipv4␣format
# make the socket listen on this port
server_socket.listen(port)
# listening forever
while True:
    client, addr = server_socket.accept()
    print("connection is established")
    while True:
        recieved_message = client.recv(1024).decode()
        if recieved_message == "CLOSE SOCKET":
            client.close()
            break
        else:
            response = recieved_message.upper()
            client.send(bytes(response.encode()))
       
    
 # when a connection to a client is␣↪accepted
 # open a conitional conection --> break the connection when 'CLOSE SOCKET' is␣↪recieved

# recieve meassage as bytes
# decoding the bytes into characters
#Check if the message was 'CLOSE SOCKET' to close connection
# otherwise capitalize the decoded message
# send the response as bytes again
    