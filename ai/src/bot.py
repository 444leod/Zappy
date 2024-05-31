#!/usr/bin/env python3

import sys
from typing import List
from connection_handler import ConnectionHandler
from config import Config
import commands as cmd

class Bot():
    def __init__(self, verbose=False, traced=False) -> None:
        self.conf: Config = Config()
        try:
            self.com_handler: ConnectionHandler = ConnectionHandler(
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
        self.cmd_sent: List[str] = []
        self.base_funcs = {
            "dead\n" : self.die,
            "message": self.receive_message  
        }

    def log(self, *args, **kargs) -> None:
        # res: str = str(*args, **kargs)
        if (self.verbose):
            print(*args, **kargs)
        if (self.traced):
            with open(".trace", "a") as f:
                print(*args, file=f)

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
            self.log(self.results[-1], end="")
            # Handle death or receiving a message by Broadcast
            key: str = self.results[-1].split(" ")[0]
            if (key in self.base_funcs):
                self.base_funcs[key]()
            # rest of logic here
            cmd_to_send = cmd.Forward()
            self.cmd_sent.append(cmd_to_send.dump())
            self.com_handler.send_command(cmd_to_send.dump())

def main() -> None:
    bot = Bot(
        verbose = True,
        traced = True
    )
    bot.run()

if __name__ == "__main__":
    main()