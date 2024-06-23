import socket

class ConnectionHandler():
    def __init__(self, hostname: str = "localhost", port: int = 5555) -> None:
        """
        Represents a connection to the server
        Attributes:
            hostname: The hostname of the server
            port: The port of the server
            sock: The socket object
        """
        self.hostname = hostname
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.hostname, self.port))

    def send_command(self, command: str) -> None:
        """
        Sends a command to the server
        """
        self.sock.send((command + "\n").encode())

    def receive_response(self) -> str:
        """
        Receives a response from the server
        """
        buff = ""
        while not buff.endswith("\n"):
            buff += self.sock.recv(1).decode()
        return buff
