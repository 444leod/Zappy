#!/usr/bin/env python3

import socket
import sys

class CommandHandler():
    def __init__(self, hostname: str = "localhost", port: int = 5555):
        self.hostname = hostname
        self.port = port
        self.sock = socket.socket()
        self.sock.connect((self.hostname, self.port))
        response = self.sock.recv(1024)
        print("res: " + response.decode(), end="")
    
    def send_command(self, command: str) -> str:
        self.sock.send(command.encode())
        response = self.sock.recv(1024)
        print(response)
        print("res: " + response.decode())

        return response.decode()

def main():
    handler = CommandHandler(
        port=5055
    )
    handler.send_command("test\n")



if __name__ == "__main__":
    main()