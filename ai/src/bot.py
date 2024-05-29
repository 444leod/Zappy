#!/usr/bin/env python3

import socket
import sys

class CommandHandler():
    def __init__(self, hostname: str = "localhost", port: int = 5555):
        self.hostname = hostname
        self.port = port
        self.sock = socket.socket()
        self.sock.connect((self.hostname, self.port))
    
    def send_command(self, command: str) -> None:
        self.sock.send(command.encode())

    def receive_response(self) -> str:
        buff = ""
        while not buff.endswith("\n"):
            buff += self.sock.recv(1).decode()
        return buff

def main():
    handler = CommandHandler(
        port=5055
    )
    handler.send_command("test\n")
    res0 = handler.receive_response()
    res1 = handler.receive_response()
    res2 = handler.receive_response()
    print("res0: '" + res0 + "'")
    print("res1: '" + res1 + "'")
    print("res2: '" + res2 + "'")



if __name__ == "__main__":
    main()