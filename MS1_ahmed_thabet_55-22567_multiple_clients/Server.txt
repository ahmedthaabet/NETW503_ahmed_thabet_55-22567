import socket
import threading

port = 4493

server_running = True

def threaded(client, addr):
    print("[NEW CONNECTION] " + str(addr) + " connected.")
    while True:
        message_received = client.recv(1024)
        if not message_received:
            break

        message_decoded = message_received.decode()
        response = message_decoded.upper()
        client.send(bytes(response.encode()))

        if message_decoded == "CLOSE SOCKET":
            break

    client.close()
    print(f"[CONNECTION CLOSED] {addr}")
    
    global server_running
    server_running = False
    print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 2}")

def main():
    global server_running
    print("Server is starting...")
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('172.20.10.2', port))
    server_socket.listen(4)

    while server_running:
        client, addr = server_socket.accept()
        threading.Thread(target=threaded, args=(client, addr)).start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")

    server_socket.close()

if __name__ == "__main__":
    main()
