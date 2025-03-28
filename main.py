import socket

HOST = "0.0.0.0"  # Listen on all network interfaces
PORT = 9999  # Choose a port

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((HOST, PORT))

print(f"UDP Server listening on {HOST}:{PORT}")

while True:
    try:
        data, addr = sock.recvfrom(1024)  # Receive up to 1024 bytes
        print(f"Received from {addr}: {data.decode()}")
        sock.sendto(b"Message received!", addr)  # Send a response
    except Exception as e:
        print(f"Error: {e}")
