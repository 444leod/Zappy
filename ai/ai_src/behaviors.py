from typing import List
from enum import Enum
import ai_src.commands as cmd
from ai_src.data import PlayerInfo, Map, Collectibles, TileContent, LEVEL_UP_REQ

class ABehavior:
    def __init__(self):
        """
        Abstract class for behaviors
        """
        self.command_stack: List[cmd.ACommand] = []
        self.inv_count: int = 0

    def mandatory_inventory(self, nb_calls) -> None:
        """
        Add an inventory command every x call
        """
        self.inv_count += 1
        if self.inv_count == nb_calls:
            self.command_stack.append(cmd.Inventory())
            self.inv_count = 0

    def get_next_command(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> cmd.ACommand:
        """
        Get the next command to execute from the stack
        """
        if not self.command_stack:
            self.generate_command_stack(player_info, map, messages)
        return self.command_stack.pop(0)
    
    def new_behavior(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> 'ABehavior': # None | ABehavior:
        """
        Get the name of the new behavior to switch to or None if no switch is needed
        """
        def analyse_message(messages: List[tuple[int, str]]) -> bool:
            try:
                message = messages[-1]
                player_dir, msg = message
                message, level = msg.split("-")
                if message != "level":
                    return False
                return int(level) == player_info.level
            except:
                return False

        if self.enough_ressources_to_incant(player_info, map):
            return IncantationLeader()
        if analyse_message(messages):
            return IncantationFollower()
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate the command stack, should be overriden by the child class
        """
        raise NotImplementedError("You are not supposed to override this method")

    def collect_food(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Collect food from the tile
        """
        for _ in range(map.tiles[player_info.pos[0]][player_info.pos[1]].collectibles.food):
            self.command_stack.append(cmd.Take("food"))
    
    def collect_all_rocks(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Collect all rocks from the tile
        """
        to_collect: dict[str, int] = map.tiles[player_info.pos[0]][player_info.pos[1]].collectibles.__dict__
        to_collect.pop("food")
        for rock, amount in to_collect.items():
            for _ in range(amount):
                self.command_stack.append(cmd.Take(rock))

    def enough_ressources_to_incant(self, player_info: PlayerInfo, map: Map) -> bool:
        """
        Check if the player is ready to incant in terms of ressources in his inv and on the tile
        """
        current_tile: TileContent = map.tiles[player_info.pos[0]][player_info.pos[1]]
        total_rocks: Collectibles = current_tile.collectibles + player_info.inv
        enough_rocks: bool = total_rocks >= LEVEL_UP_REQ[player_info.level].collectibles
        return enough_rocks and player_info.inv.food >= 4

    def easy_evolve(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Try to evolve to the next level if the requirements are met
        !!! ASSUMES THAT THE PLAYERS ARE THE SAME LEVEL !!!
        """
        current_tile: TileContent = map.tiles[player_info.pos[0]][player_info.pos[1]]
        enough_players: bool = current_tile.nb_players >= LEVEL_UP_REQ[player_info.level].nb_players

        if enough_players and self.generate_command_stack():
            rocks_to_set: Collectibles = LEVEL_UP_REQ[player_info.level].collectibles - current_tile.collectibles
            rocks_to_set.neg_to_zero()
            for rock, amount in rocks_to_set.__dict__.items():
                for _ in range(amount):
                    self.command_stack.append(cmd.Set(rock))
            self.command_stack.append(cmd.Incantation())

class LookingForward(ABehavior):
    def __init__(self):
        """
        LookingForward behavior, dummy behavior that looks and moves forwards
        """
        super().__init__()

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate the command stack for the LookingForward behavior
        """
        super().collect_food(player_info, map)
        super().collect_all_rocks(player_info, map)
        self.command_stack.append(cmd.Look())
        self.command_stack.append(cmd.Forward())
        self.command_stack.append(cmd.Inventory())

class Manual(ABehavior):
    def __init__(self):
        """
        Manual behavior, the player is controlled by the user
        """
        super().__init__()
        print("r for right, l for left, f for forward, i for inventory, t>item for take, s>item for set, I for incantation, L for look, b for broadcast")

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate a command by the user
        """
        while True:
            tab = input("Enter a command: ").split(">")
            if len(tab) == 1:
                user_input = tab[0]
                rest = ""
            elif len(tab) == 2:
                user_input, rest = tab
            else:
                continue
            cmd_to_send: cmd.ACommand = None
            match user_input:
                case "r": cmd_to_send = cmd.Right(); break
                case "l": cmd_to_send = cmd.Left(); break
                case "f": cmd_to_send = cmd.Forward(); break
                case "i": cmd_to_send = cmd.Inventory(); break
                case "t": cmd_to_send = cmd.Take(rest); break
                case "s": cmd_to_send = cmd.Set(rest); break
                case "I": cmd_to_send = cmd.Incantation(); break
                case "L": cmd_to_send = cmd.Look(); break
                case "b": cmd_to_send = cmd.Broadcast(rest); break
        
        self.command_stack.append(cmd_to_send)

class IncantationLeader(ABehavior):
    def __init__(self):
        """
        IncantationLeader behavior, the player is the leader of the incantation
        """
        super().__init__()
        self.players_ready_to_level_up: int = 1
        self.reset: bool = False

    def new_behavior(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> ABehavior:
        if player_info.inv.food < 4 or self.reset:
            return player_info.old_behavior
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate the command stack for the IncantationLeader behavior
        """
        super().mandatory_inventory(10)
        if self.players_ready_to_level_up >= LEVEL_UP_REQ[player_info.level].nb_players:
            self.reset = True
            self.command_stack.append(cmd.Incantation())
        else:
            self.command_stack.append(cmd.Broadcast(f"level-{player_info.level}"))

class IncantationFollower(ABehavior):
    class State(Enum):
        MOVING = 0
        WAITING = 1
        ARRIVED = 2
        ABANDONED = 3

    def __init__(self):
        """
        IncantationFollower behavior, the player is a follower of the incantation
        """
        super().__init__()
        self.state: IncantationFollower.State = IncantationFollower.State.MOVING


    def new_behavior(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> ABehavior:
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate the command stack for the IncantationFollower behavior
        """
        print("this is a follower")
        if player_info.inv.food < 4:
            self.command_stack.append(cmd.Inventory())
            return
        self.command_stack.append(cmd.Inventory())

