import socket

class ConnectionHandler():
    def __init__(self, hostname: str = "localhost", port: int = 5555) -> None:
        self.hostname = hostname
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.hostname, self.port))

    def send_command(self, command: str) -> None:
        self.sock.send((command + "\n").encode())

    def receive_response(self) -> str:
        buff = ""
        while not buff.endswith("\n"):
            buff += self.sock.recv(1).decode()
        return buff
