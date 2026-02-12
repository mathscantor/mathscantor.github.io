import socket, ssl

ip = "127.0.0.1"
port = 4443

# Set up listener
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((ip, port))
sock.listen(5)
print(f"Listening on {ip}:{port}")

# Create SSLContext object using server key and cert + verify connection using client's CA cert.
ssl_ctx = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)

ssl_ctx.options |= ssl.OP_NO_SSLv2 | ssl.OP_NO_SSLv3
ssl_ctx.check_hostname = False
ssl_ctx.load_cert_chain(certfile="server.crt", keyfile="server.key")
ssl_ctx.load_verify_locations(cafile="client_ca.crt")
ssl_ctx.verify_mode = ssl.CERT_REQUIRED

# Wait for incoming connection
while True:
    newsock, addr = sock.accept()
    try:
        sslsock = ssl_ctx.wrap_socket(newsock, server_side=True)
    except (ssl.SSLError, ssl.SSLEOFError )as e:
        print(e)
        newsock.close()
        continue
    try:
        print("TLS established:", sslsock.getpeercert())
        data = sslsock.recv(1024)
        print("Received:", data.decode())
        sslsock.sendall(b"Hello from server")
    except Exception as e:
        print("Error:", e)
    finally:
        sslsock.close()