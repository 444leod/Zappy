#!/usr/bin/env python3

import socket
import sys
from typing import List
import commands

USAGE = "USAGE: ./zappy_ai -p port -n name -h machine"

class Config:
    def __init__(self) -> None:
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

class Bot():
    def __init__(self, verbose=False, traced=False) -> None:
        self.conf: Config = Config()
        try:
            self.com_handler: CommandHandler = CommandHandler(
                port=self.conf.port,
                hostname=self.conf.machine
            )
        except Exception as e:
            print("Failed to connect to server: " + str(e))
            sys.exit(84)
        self.verbose: bool = verbose
        self.traced: bool = traced
        self.results: List[str] = []
        self.results.append(self.com_handler.receive_response())
        if (self.results[-1] != "WELCOME\n"):
            print("Failed to connect to server: " + self.results[-1])
            sys.exit(84)
        self.com_handler.send_command(self.conf.name)
        self.results.append(self.com_handler.receive_response())
        self.results.append(self.com_handler.receive_response())
        #tmp bc I'll have a class for relevant data later on
        tmpNbEggs: int = int(self.results[-2])
        tmpX, tmpY = map(int, self.results[-1].split())
        self.log(f"{tmpNbEggs=}")
        self.log(f"{tmpX=} {tmpY=}")
        self.messages_received: List[tuple[int, str]] = [] # [(playerID, message), ..]
        self.messages_sent: List[str] = []
        self.base_funcs = {
            "dead\n" : self.die,
            "message": self.receive_message  
        }

    def log(self, *args, **kargs) -> None:
        res: str = str(*args, **kargs)
        if (self.verbose):
            print(res)
        if (self.traced):
            with open(".trace", "a") as f:
                print(res, file=f)

    def die(self) -> None:
        self.log("Bot died. Exiting.")
        sys.exit(0)

    def receive_message(self) -> None:
        tab: List[str] = self.results[-1].split(" ")
        if (len(tab) != 3) or not (tab[1][:-1].isdigit()):
            return
        self.messages_received.append((int(tab[1][:-1]), tab[2]))

    def run(self) -> None:
        while True:
            self.results.append(self.com_handler.receive_response())
            self.log(self.results[-1])
            # Handle death or receiving a message by Broadcast
            key: str = self.results[-1].split(" ")[0]
            if (key in self.base_funcs):
                self.base_funcs[key]()
            # rest of logic here

def main() -> None:
    bot = Bot(
        verbose = True,
        traced = True
    )
    bot.run()

if __name__ == "__main__":
    main()