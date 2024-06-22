from typing import List
from enum import Enum
from json import dumps
import ai_src.commands as cmd
from ai_src.data import PlayerInfo, Map, Collectibles, TileContent, Message, MessageContent, LEVEL_UP_REQ

class ABehavior:
    # Public methods used by the bot to get the next command
    def __init__(self):
        """
        Abstract class for behaviors
        """
        self.command_stack: List[cmd.ACommand] = []
        self.inv_count: int = 0

    def get_next_command(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> cmd.ACommand:
        """
        Get the next command to execute from the stack
        """
        if not self.command_stack:
            self.generate_command_stack(player_info, map, new_messages)
        return self.command_stack.pop(0)
    
    def new_behavior(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> 'ABehavior': # None | ABehavior:
        """
        Get the name of the new behavior to switch to or None if no switch is needed
        """
        def analyse_message(new_messages: List[Message]) -> bool:
            for i in range(1, len(new_messages) + 1):
                mess_content = new_messages[-i].message_content
                if mess_content == None:
                    continue
                if mess_content.message_type == MessageContent.MessageType.LEADER_READY_FOR_INCANTATION and mess_content.sender_level == player_info.level: 
                    return True
        if player_info.inv.food < 4:
            return None

        if self.enough_ressources_to_incant(player_info, map):
            return IncantationLeader()
        if analyse_message(new_messages):
            return IncantationFollower()
        return None

    # Private utility methods that can be used by any behavior
    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
        """
        Generate the command stack, should be overriden by the child class
        """
        raise NotImplementedError("You are not supposed to override this method")

    def refresh_inventory(self, nb_calls) -> None:
        """
        Add an inventory command every x call
        """
        self.inv_count += 1
        if self.inv_count == nb_calls:
            self.command_stack.append(cmd.Inventory())
            self.inv_count = 0

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

    def set_missing_rocks(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Set the missing rocks to incant
        """
        current_tile: TileContent = map.tiles[player_info.pos[0]][player_info.pos[1]]
        rocks_to_set: Collectibles = LEVEL_UP_REQ[player_info.level].collectibles - current_tile.collectibles
        rocks_to_set.neg_to_zero()
        for rock, amount in rocks_to_set.__dict__.items():
            for _ in range(amount):
                self.command_stack.append(cmd.Set(rock))

    def easy_evolve(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Try to evolve to the next level if the requirements are met
        !!! ASSUMES THAT THE PLAYERS ARE THE SAME LEVEL !!!
        """
        current_tile: TileContent = map.tiles[player_info.pos[0]][player_info.pos[1]]
        enough_players: bool = current_tile.nb_players >= LEVEL_UP_REQ[player_info.level].nb_players

        if enough_players and self.enough_ressources_to_incant(player_info, map):
            rocks_to_set: Collectibles = LEVEL_UP_REQ[player_info.level].collectibles - current_tile.collectibles
            rocks_to_set.neg_to_zero()
            for rock, amount in rocks_to_set.__dict__.items():
                for _ in range(amount):
                    self.command_stack.append(cmd.Set(rock))
            self.command_stack.append(cmd.Incantation())

    def go_to_direction(self, direction: int) -> None:
        """
        Go to a certain direction
        Note: the direction is 0 to 8
        Exemple when the player's orientation is East:
            x x x       4 3 2
            x > x ----> 5 0 1
            x x x       6 7 8
        """
        print(f"Going to direction {direction}")
        if direction == 0:
            print("ALERT: The player is already at the right position")
            self.command_stack.append(cmd.ConnectNbr()) # Instant Command, useful for waiting
            return
        
        if not (0 < direction < 8):
            print("ALERT: somethin went really wrong with the direction")
            self.command_stack.append(cmd.ConnectNbr()) # Instant Command, useful for waiting
            return
                    
        if direction in [3, 4]:
            self.command_stack.append(cmd.Left())
        
        if direction in [6, 7]:
            self.command_stack.append(cmd.Right())
        
        if direction == 5:
            self.command_stack.append(cmd.Right())
            self.command_stack.append(cmd.Right())

        self.command_stack.append(cmd.Forward())

class LookingForward(ABehavior):
    def __init__(self):
        """
        LookingForward behavior, dummy behavior that looks and moves forwards
        """
        super().__init__()

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
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

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
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
        self.players_ready_to_level_up: List[str] = []
        self.reset: bool = False

    def new_behavior(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> ABehavior:
        if player_info.inv.food < 4 or self.reset:
            return player_info.old_behavior
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
        """
        Generate the command stack for the IncantationLeader behavior
        """
        super().refresh_inventory(10)
        if player_info.uuid not in self.players_ready_to_level_up:
            self.players_ready_to_level_up.append(player_info.uuid)
        for message in new_messages:
            mess_content = message.message_content
            if mess_content == None:
                continue
            if (mess_content.sender_level == player_info.level
                and mess_content.target_uuid == player_info.uuid):
                if (mess_content.message_type == MessageContent.MessageType.FOLLOWER_READY_FOR_INCANTATION
                    and mess_content.sender_uuid not in self.players_ready_to_level_up):
                    self.players_ready_to_level_up.append(mess_content.sender_uuid)
                if (mess_content.message_type == MessageContent.MessageType.FOLLOWER_ABANDONED_INCANTATION
                    and mess_content.sender_uuid in self.players_ready_to_level_up):
                    self.players_ready_to_level_up.remove(mess_content.sender_uuid)

        if player_info.inv.food < 4:
            self.command_stack.append(cmd.Broadcast(dumps(vars(MessageContent(
                message_type=MessageContent.MessageType.LEADER_ABANDONED_INCANTATION,
                team_name=player_info.team_name,
                sender_uuid=player_info.uuid,
                sender_level=player_info.level,
                target_uuid=""
            )))))

        if len(self.players_ready_to_level_up) >= LEVEL_UP_REQ[player_info.level].nb_players:
            self.reset = True
            self.command_stack.append(cmd.Broadcast(dumps(vars(MessageContent(
                message_type=MessageContent.MessageType.LEADER_LAUCHING_INCANTATION,
                team_name=player_info.team_name,
                sender_uuid=player_info.uuid,
                sender_level=player_info.level,
                target_uuid=""
            )))))
            self.set_missing_rocks(player_info, map)
            self.command_stack.append(cmd.Incantation())
        else:
            self.command_stack.append(cmd.Broadcast(dumps(vars(MessageContent(
                message_type=MessageContent.MessageType.LEADER_READY_FOR_INCANTATION,
                team_name=player_info.team_name,
                sender_uuid=player_info.uuid,
                sender_level=player_info.level,
                target_uuid=""
            )))))

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
        self.destination_direction: int = 0
        self.starting_level: int = 0

    def new_behavior(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> ABehavior:
        if self.state == IncantationFollower.State.ABANDONED:
            return player_info.old_behavior
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
        """
        Generate the command stack for the IncantationFollower behavior
        """
        def check_position() -> bool:
            """
            Check if the player is at the right position (on top of the IncantationLeader)
            """
            try:
                message: tuple[int, str] = new_messages[-1]
                self.destination_direction, msg = message
                message, level = msg.split("-")
                if message != "level" or int(level) != player_info.level:
                    return False
                if self.destination_direction == 0:
                    return True
            except:
                return False

        self.starting_level = player_info.level if self.starting_level == 0 else self.starting_level

        if check_position():
            self.state = IncantationFollower.State.ARRIVED
        if player_info.inv.food < 4:
            self.state = IncantationFollower.State.ABANDONED
        if self.starting_level != player_info.level:
            self.state = IncantationFollower.State.ABANDONED

        match self.state:
            case IncantationFollower.State.MOVING: super().go_to_direction(self.destination_direction)
            case IncantationFollower.State.WAITING: self.command_stack.append(cmd.ConnectNbr())
            case IncantationFollower.State.ARRIVED:
                # Say that the player is here using unique ID
                self.command_stack.append(cmd.Broadcast("Imhere"))
                self.state = IncantationFollower.State.WAITING
            case IncantationFollower.State.ABANDONED:
                # Say that the player is not here using unique ID
                self.command_stack.append(cmd.Broadcast("Im2old4this"))
        super().refresh_inventory(5)
