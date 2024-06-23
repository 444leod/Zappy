#!/usr/bin/env python3

import sys
from typing import List
from json import dumps, loads
from ai_src.connection_handler import ConnectionHandler
from ai_src.config import Config, HelpException, ArgError
from ai_src.data import PlayerInfo, Collectibles, Map, TileContent, Message, MessageContent
from ai_src.behaviors import Manual, ABehavior, Harvester, Distractor
import ai_src.commands as cmd
from ai.ai_src.utils import add_tuples, turn_left, turn_right
import random as rd

class Bot():
    def __init__(self, verbose: bool=False, traced: bool=False) -> None:
        """
        Represents an instance of a bot playing the game
        Attributes:
            verbose: Whether to print debug messages
            traced: Whether to log debug messages to a file
        """
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
        self.nb_eggs = int(self.results[-2])

        self.player_info: PlayerInfo = PlayerInfo()

        self.map: Map = Map()
        self.map.map_size = tuple(map(int, self.results[-1].split()))
        self.map.tiles = [[TileContent() for _ in range(self.map.map_size[0])] for _ in range(self.map.map_size[1])]
        self.map.tiles[0][0].nb_players = 1

        self.messages_received_buffer: List[Message] = []
        self.messages_received: List[Message] = []
        self.messages_sent: List[Message] = []
        self.cmd_sent: List[str] = []
        self.base_funcs = {
            "dead\n" : self.die,
            "message": self.receive_broadcast,
            "Elevation": lambda: self.log("HANDLE ELEVATION"),
            "Current": self.level_up,
            "ko\n": lambda: self.log("FAILED ELEVATION"),
            "Elevation": lambda: self.log("HANDLE ELEVATION"),
            "Current": self.level_up,
            "ko\n": lambda: self.log("FAILED ELEVATION"),
        }
        self.current_behavior = (Manual() if self.conf.manual else Distractor() if rd.randint(0, 5) == 0 else Harvester())
        self.player_info.old_behavior = self.current_behavior

    def run(self) -> None:
        """
        Main loop of the bot
        The only function that should be called from the outside
        """
        while True:
            self.behavior_logic()
            self.receive_command()
            self.handle_commands_sent()

    def log(self, *args, **kargs) -> None:
        """
        Logs the message to stdout and to a file if tracing is enabled
        """
        if (self.verbose):
            print(*args, **kargs)
        if (self.traced):
            with open(".trace", "a") as f:
                print(*args, file=f)

    def die(self) -> None:
        """
        Handle the bot's death
        """
        self.log("Bot died. Exiting.")
        sys.exit(0)

    def receive_broadcast(self) -> None:
        """
        Handle receiving a broadcast message
        """
        tab: List[str] = self.results[-1].split(" ")
        if (len(tab) != 3) or not (tab[1][:-1].isdigit()):
            return
        try:
            tmp: dict = loads(tab[2].replace("'", '"'))
            message_content = MessageContent(message_type=MessageContent.MessageType(tmp.pop("message_type")), **tmp)
        except:
            message_content = None
        self.messages_received_buffer.append(Message(
            sender_direction=int(tab[1][:-1]),
            raw_content=tab[2],
            message_content=message_content
        ))

    def level_up(self) -> None:
        """
        Handle the bot's level up via incantation
        """
        self.player_info.level += 1

    def behavior_logic(self) -> None:
        """
        Handle the bot's behavior
        """
        new_behavior: ABehavior | None = self.current_behavior.new_behavior(self.player_info, self.map, self.messages_received_buffer)
        if new_behavior is not None and not self.conf.manual:
            self.current_behavior = new_behavior
        cmd_to_send: cmd.ACommand = self.current_behavior.get_next_command(self.player_info, self.map, self.messages_received_buffer)
        self.log(cmd_to_send.dump())
        self.cmd_sent.append(cmd_to_send.dump())
        self.com_handler.send_command(cmd_to_send.dump())
        while self.messages_received_buffer != []:
            self.messages_received.append(self.messages_received_buffer.pop(0))

    def receive_command(self) -> None:
        """
        Receive a command from the server
        Also handles death and broadcast messages
        """
        while True:
            # Wait for the response
            self.results.append(self.com_handler.receive_response())
            self.log(self.results[-1], end="")

            # Handle death or receiving a message by Broadcast
            key: str = self.results[-1].split(" ")[0]
            if (key in self.base_funcs):
                self.base_funcs[key]()
                if key in ["ko\n", "Current"]: return
                continue
            # Returning to the main loop if the response is not a message or a death
            return
        
    def handle_forward(self) -> None:
        """
        Handle the forward command
        """
        self.map.tiles[self.player_info.pos[0]][self.player_info.pos[1]].nb_players -= 1
        self.player_info.pos = add_tuples(self.player_info.pos, self.player_info.orientation)
        self.player_info.pos = (self.player_info.pos[0] % self.map.map_size[0], self.player_info.pos[1] % self.map.map_size[1])
        self.map.player_pos = self.player_info.pos
        self.map.tiles[self.player_info.pos[0]][self.player_info.pos[1]].nb_players += 1

    def handle_look(self) -> None:
        """
        Handle the look command
        """
        self.map.vision_update(
            cmd.Look().interpret_result(self.results[-1]),
            self.player_info.orientation,
            self.player_info.pos
        )
    
    def handle_eject(self) -> None:
        """
        Handle the eject command
        """
        try :
            cmd.Eject().interpret_result(self.results[-1])
            self.map.tiles[self.player_info.pos[0]][self.player_info.pos[1]].nb_players = 1
        except Exception:
            pass

    def handle_fork(self) -> None:
        """
        Handle the fork command
        """
        try:
            cmd.Fork().interpret_result(self.results[-1])
            self.nb_eggs += 1
        except Exception as e:
            self.log(e)
            self.log("Failed to fork")

    def handle_take(self, object: str) -> None:
        """
        Handle the take command
        """
        try:
            pos = self.player_info.pos
            cmd.Set().interpret_result(self.results[-1])
            self.player_info.inv.add_object_by_name(object)
            self.map.tiles[pos[0]][pos[1]].collectibles.remove_object_by_name(object)
        except Exception as e:
            self.map.tiles[pos[0]][pos[1]].collectibles.remove_all_objects_by_name(object)
            self.log(e)
            self.log("Failed to take object")

    def handle_set(self, object: str) -> None:
        """
        Handle the set command
        """
        try:
            pos = self.player_info.pos
            cmd.Set().interpret_result(self.results[-1])
            self.player_info.inv.remove_object_by_name(object)
            self.map.tiles[pos[0]][pos[1]].collectibles.add_object_by_name(object)
        except Exception as e:
            self.log(e)
            self.log("Failed to set object")

    def handle_incantation(self) -> None:
        """
        Handle the incantation command
        """
        try:
            cmd.Incantation().interpret_result(self.results[-1])
        except Exception as e:
            self.log(e)
            self.log("Failed to incant")

    def handle_broadcast(self) -> None:
        """
        Handle the broadcast command
        """
        print(self.results[-1])
        res = cmd.Broadcast().interpret_result(self.results[-1])
        self.messages_sent.append(res)
        

    def handle_commands_sent(self) -> None:
        """
        Handle the commands sent by the bot
        Loop that handles the commands sent by the bot
        """
        cmd_sent: str = self.cmd_sent[-1].split(" ")[0]
        try :
            cmd_sup: str = self.cmd_sent[-1].split(" ")[1]
        except IndexError:
            cmd_sup = ""
        match cmd_sent:
            case "Inventory": self.player_info.inv = Collectibles(**(cmd.Inventory().interpret_result(self.results[-1])))
            case "Look": self.handle_look()
            case "Forward": self.handle_forward()
            case "Right": self.player_info.orientation = turn_right(self.player_info.orientation)
            case "Left": self.player_info.orientation = turn_left(self.player_info.orientation)
            case "Broadcast": self.handle_broadcast()
            case "Connect_nbr": self.nb_eggs = int(self.results[-1]) if self.results[-1].isdigit() else self.nb_eggs
            case "Eject": self.handle_eject()
            case "Fork": self.handle_fork()
            case "Take": self.handle_take(cmd_sup)
            case "Set": self.handle_set(cmd_sup)
            case "Incantation": self.handle_incantation()

def main() -> None:
    bot = Bot(
        verbose = True,
        traced = True
    )
    bot.run()

if __name__ == "__main__":
    main()