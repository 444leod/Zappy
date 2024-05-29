#!/usr/bin/env python3

import socket
import sys

USAGE = "USAGE: ./zappy_ai -p port -n name -h machine"

class Config:
    def __init__(self):
        argv = sys.argv
        if (len(argv) == 1):
            print(USAGE)
            sys.exit(84)
        if (argv[1] == "--help"):
            print(USAGE)
            sys.exit(0)
        try:
            self.port: int = int(argv[argv.index("-p") + 1])
            self.name: str = argv[argv.index("-n") + 1]
        except Exception as _:
            print(USAGE)
            sys.exit(84)
        try:
            self.machine: str = argv[argv.index("-h") + 1]
        except ValueError:
            self.machine = "localhost"
        except IndexError:
            print(USAGE)
            sys.exit(84)
        if (self.name == "GRAPHIC"):
            print("Name can't be 'GRAPHIC' as it's reserved for the GUI.")
            print(USAGE)
            sys.exit(84)

class CommandHandler():
    def __init__(self, hostname: str = "localhost", port: int = 5555):
        self.hostname = hostname
        self.port = port
        self.sock = socket.socket()
        self.sock.connect((self.hostname, self.port))
    
    def send_command(self, command: str) -> None:
        self.sock.send((command + "\n").encode())

    def receive_response(self) -> str:
        buff = ""
        while not buff.endswith("\n"):
            buff += self.sock.recv(1).decode()
        return buff

def main():
    conf = Config()
    try:
        handler = CommandHandler(
            port=conf.port,
            hostname=conf.machine
        )
    except Exception as e:
        print("Failed to connect to server: " + str(e))
        sys.exit(84)
    handler.send_command(conf.name)
    res0 = handler.receive_response()
    res1 = handler.receive_response()
    res2 = handler.receive_response()
    print("res0: '" + res0 + "'")
    print("res1: '" + res1 + "'")
    print("res2: '" + res2 + "'")

if __name__ == "__main__":
    main()