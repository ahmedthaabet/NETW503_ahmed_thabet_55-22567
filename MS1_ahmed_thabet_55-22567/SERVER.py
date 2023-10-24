import socket
import threading
PORT = 22567
ADDR = ('127.0.0.1', PORT)
def threaded(client, addr):
    
    print("[NEW CONNECTION] " + str(ADDR) + " connected.")
    print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1-7}")
    while True :
        
        recieved_message = client.recv(1024).decode()
        if recieved_message == "CLOSE SOCKET":
            break
        response = recieved_message.upper()
        client.send(bytes(response.encode()))
    
    print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1-8}")

    client.close()
# Functionality of the server
#
#
# do not forget to release the thread if you've locked it
def main():
    
    print(" Server is starting...")
    #initiate server socket with the TCP connection
    server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    # binding the server socket with the localhost as ip and port number
    port=22567
    server_socket.bind(('127.0.0.1',port)) # '127.0.0.1' is the localhost in ipv4␣format
    # make the socket listen on this port
    server_socket.listen(20)
    # listening forever
    print(" server has started, waiting for a connection") 
# Open server socket as in MS0
#
#
    while True:
        
        client, addr = server_socket.accept()
# Locking the thread that will be assigned to the client
        threading.Lock().acquire()
        ClientThread = threading.Thread(target=threaded, args=(client,addr))
        #print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")
        ClientThread.start()
        #print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")
# start new thread
#
#
       
if __name__ == "__main__":
    main()