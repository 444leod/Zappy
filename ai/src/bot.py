#!/usr/bin/env python3

import sys
from typing import List
from connection_handler import ConnectionHandler
from config import Config
from enum import Enum
import commands as cmd
from dataclasses import dataclass, field

class Orientation(Enum):
    NORTH = 1
    EAST = 2
    SOUTH = 3
    WEST = 4

@dataclass
class Inventory():
    food: int = 10
    linemate: int = 0
    deraumere: int = 0
    sibur: int = 0
    mendiane: int = 0
    phiras: int = 0
    thystame: int = 0

@dataclass
class PlayerInfo():
    level: int = 1
    inv: Inventory = field(default_factory=Inventory)
    pos: tuple[int, int] = (0, 0)
    orientation: Orientation = Orientation.NORTH

@dataclass
class GeneralInfo():
    map_size: tuple[int, int] = (0, 0)
    nb_eggs: int = 0

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
        self.results: List[str] = []
        self.results.append(self.com_handler.receive_response())
        if (self.results[-1] != "WELCOME\n"):
            print("Failed to connect to server: " + self.results[-1])
            sys.exit(84)

        self.com_handler.send_command(self.conf.name)
        self.results.append(self.com_handler.receive_response())
        self.results.append(self.com_handler.receive_response())

        self.verbose: bool = verbose
        self.traced: bool = traced

        self.general_info: GeneralInfo = GeneralInfo()
        self.general_info.map_size = tuple(map(int, self.results[-1].split()))
        self.general_info.nb_eggs = int(self.results[-2])

        self.player_info: PlayerInfo = PlayerInfo()

        self.messages_received: List[tuple[int, str]] = [] # [(playerID, message), ..]
        self.messages_sent: List[str] = []
        self.cmd_sent: List[str] = []
        self.base_funcs = {
            "dead\n" : self.die,
            "message": self.receive_broadcast  
        }

    def log(self, *args, **kargs) -> None:
        if (self.verbose):
            print(*args, **kargs)
        if (self.traced):
            with open(".trace", "a") as f:
                print(*args, file=f)

    def die(self) -> None:
        self.log("Bot died. Exiting.")
        sys.exit(0)

    def receive_broadcast(self) -> None:
        tab: List[str] = self.results[-1].split(" ")
        if (len(tab) != 3) or not (tab[1][:-1].isdigit()):
            return
        self.messages_received.append((int(tab[1][:-1]), tab[2]))

    def run(self) -> None:
        while True:
            # Behavior logic here
            cmd_to_send = cmd.Inventory()
            self.cmd_sent.append(cmd_to_send.dump())
            self.com_handler.send_command(cmd_to_send.dump())

            # Wait for the response
            self.results.append(self.com_handler.receive_response())
            self.log(self.results[-1], end="")

            # Handle death or receiving a message by Broadcast
            key: str = self.results[-1].split(" ")[0]
            if (key in self.base_funcs):
                self.base_funcs[key]()
                continue

            # Handle the command sent
            if (self.cmd_sent[-1] == cmd.Inventory().dump()):
                self.player_info.inv = Inventory(**(cmd_to_send.interpret_result(self.results[-1])))
                self.log(self.player_info.inv)

def main() -> None:
    bot = Bot(
        verbose = True,
        traced = True
    )
    bot.run()

if __name__ == "__main__":
    main()