import socket

# Host IP and port
host = '0.0.0.0'  # Listen on all network interfaces
port = 12345  # Port to listen on

# Create socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen()

print(f"Listening on {port}...")

# Accept connections
while True:
    client_socket, address = server_socket.accept()
    print(f"Connection from {address} has been established.")

    # Receive data
    while True:
        data = client_socket.recv(1024)
        if not data:
            break  # Connection closed
        print(data.decode('utf-8'))

    client_socket.close()