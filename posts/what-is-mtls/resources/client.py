import socket, ssl

server_ip = "127.0.0.1"
server_port = 4443

# TCP Handshake
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((server_ip, server_port))

# Create SSLContext object using client key and cert + verify connection using server's CA cert.
ssl_ctx = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
    
ssl_ctx.options |= ssl.OP_NO_SSLv2 | ssl.OP_NO_SSLv3
ssl_ctx.check_hostname = True
ssl_ctx.load_cert_chain(certfile="client.crt", keyfile="client.key")
ssl_ctx.load_verify_locations(cafile="server_ca.crt")
ssl_ctx.verify_mode = ssl.CERT_REQUIRED

# Abstract mTLS session
sslsock = ssl_ctx.wrap_socket(sock, server_hostname="server.mtls.example.org")

# Send data to server
sslsock.sendall(b"Hello from client")
print("Server says:", sslsock.recv(1024).decode())