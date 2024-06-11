#!/usr/bin/env python3

import sys
from typing import List
from ai_src.connection_handler import ConnectionHandler
from ai_src.config import Config, HelpException, ArgError
from ai_src.data import PlayerInfo, GeneralInfo, Orientation, Collectibles, Map, TileContent
import ai_src.commands as cmd
from ai_src.utiles import add_tuples, turn_left, turn_right

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
            cmd_to_send: cmd.ACommand = cmd.ConnectNbr()
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
        cmd_sent: str = self.cmd_sent[-1].split(" ")[0]
        match cmd_sent:
            case "Inventory":
                self.player_info.inv = Collectibles(**(cmd.Inventory().interpret_result(self.results[-1])))
            case "Look":
                self.map.vision_update(
                    cmd.Look().interpret_result(self.results[-1]),
                    self.player_info.orientation,
                    self.player_info.pos
                )
            case "Forward":
                self.map[self.player_info.pos].nb_players -= 1
                self.player_info.pos = add_tuples(self.player_info.pos, self.player_info.orientation.value)
                self.map[self.player_info.pos].nb_players += 1
            case "Right": 
                self.player_info.orientation = turn_right(self.player_info.orientation)
            case "Left":
                self.player_info.orientation = turn_left(self.player_info.orientation)
            case "Broadcast":
                self.messages_sent.append(cmd.Broadcast().interpret_result(self.results[-1]))
            case "Connect_nbr":
                cmd.ConnectNbr().interpret_result(self.results[-1])
            case "Eject":
                try :
                    cmd.Eject().interpret_result(self.results[-1])
                    self.map[self.player_info.pos].nb_player = 1
                except Exception:
                    pass
            case _:
                pass
        
            

def main() -> None:
    bot = Bot(
        verbose = True,
        traced = True
    )
    bot.run()

if __name__ == "__main__":
    main()