#!/usr/bin/env python3

import sys
from typing import List
from connection_handler import ConnectionHandler
from config import Config, HelpException, ArgError
from enum import Enum
import commands as cmd
from dataclasses import dataclass, field

class Orientation(Enum):
    NORTH = 1
    EAST = 2
    SOUTH = 3
    WEST = 4

@dataclass
class Collectibles():
    food: int = 0
    linemate: int = 0
    deraumere: int = 0
    sibur: int = 0
    mendiane: int = 0
    phiras: int = 0
    thystame: int = 0

    def __repr__(self) -> str:
        return f"f{self.food}l{self.linemate}d{self.deraumere}s{self.sibur}m{self.mendiane}p{self.phiras}t{self.thystame}"

@dataclass
class PlayerInfo():
    level: int = 1
    inv: Collectibles = field(default_factory=lambda: Collectibles(food=10))
    pos: tuple[int, int] = (0, 0)
    orientation: Orientation = Orientation.NORTH

@dataclass
class GeneralInfo():
    map_size: tuple[int, int] = (0, 0)
    nb_eggs: int = 0

@dataclass
class TileContent():
    collectibles: Collectibles = field(default_factory=Collectibles)
    hasSelf: bool = False

    def __repr__(self) -> str:
        return f"({self.collectibles}P{'1' if self.hasSelf else '0'})"

@dataclass
class Map():
    tiles: List[List[TileContent]] = field(default_factory=list)

    def __repr__(self) -> str:
        res = ""
        for row in self.tiles:
            res += f"{row}\n"
        return res

class Bot():
    def __init__(self, verbose=False, traced=False) -> None:
        try:
            self.conf: Config = Config()
            self.com_handler: ConnectionHandler = ConnectionHandler(
                port=self.conf.port,
                hostname=self.conf.machine
            )
        except HelpException as e:
            print(str(e))
            sys.exit(0)
        except ArgError as e:
            print(str(e))
            sys.exit(84)
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
        if (self.results[-1] == "ko\n"):
            print("Unkowned team name")
            sys.exit(84)
        self.results.append(self.com_handler.receive_response())

        self.verbose: bool = verbose
        self.traced: bool = traced

        self.general_info: GeneralInfo = GeneralInfo()
        self.general_info.map_size = tuple(map(int, self.results[-1].split()))
        self.general_info.nb_eggs = int(self.results[-2])

        self.player_info: PlayerInfo = PlayerInfo()

        self.map: Map = Map()
        self.map.tiles = [[TileContent() for _ in range(self.general_info.map_size[0])] for _ in range(self.general_info.map_size[1])]
        self.log(self.map)

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
            # Behavior logic here, send one command at a time!!
            cmd_to_send: cmd.ACommand = cmd.Look()
            self.cmd_sent.append(cmd_to_send.dump())
            self.com_handler.send_command(cmd_to_send.dump())

            self.base_funcs_loop()

            self.handle_commands_sent()
    
    def base_funcs_loop(self) -> None:
        while True:
            # Wait for the response
            self.results.append(self.com_handler.receive_response())
            self.log(self.results[-1], end="")

            # Handle death or receiving a message by Broadcast
            key: str = self.results[-1].split(" ")[0]
            if (key in self.base_funcs):
                self.base_funcs[key]()
                continue
            # Returning to the main loop if the response is not a message or a death
            return

    def handle_commands_sent(self) -> None:
        # Handle the command sent
        if (self.cmd_sent[-1] == cmd.Inventory().dump()):
            self.player_info.inv = Collectibles(**(cmd.Inventory().interpret_result(self.results[-1])))
        
        if (self.cmd_sent[-1] == cmd.Look().dump()):
            self.log(cmd.Look().interpret_result(self.results[-1]))
        
        #TODO: Handle other commands

def main() -> None:
    bot = Bot(
        verbose = True,
        traced = True
    )
    bot.run()

if __name__ == "__main__":
    main()