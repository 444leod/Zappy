from typing import List
from enum import Enum
from json import dumps
import ai_src.commands as cmd
from ai_src.data import PlayerInfo, Map, Collectibles, TileContent, Message, MessageContent, LEVEL_UP_REQ, NORTH, EAST, SOUTH, WEST
import time

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

        if analyse_message(new_messages):
            return IncantationFollower()
        elif self.enough_ressources_to_incant(player_info, map):
            return IncantationLeader()
        return None

    # Private utility methods that can be used by any behavior
    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
        """
        Generate the command stack, should be overriden by the child class
        """
        raise NotImplementedError("You are not supposed to override this method")
    
    def collect_all_on_tiles(self, pos :tuple[int,int], map: Map) -> None:
        """
        Collect all rocks from the tile
        """
        tmp: dict[str, int] = map.tiles[pos[0]][pos[1]].collectibles.__dict__
        for collectibles, amount in tmp.items():
            for _ in range(amount):
                self.command_stack.append(cmd.Take(collectibles))
    
    def turn(self, current_rotation: tuple[int, int], new_rotation: tuple[int, int]) -> None:
        """
        Turn the player to a specific orientation
        """
        current_dir = current_rotation
        new_dir = new_rotation

        if current_dir == new_dir:
            return

        # Determine the minimal rotation
        rotations = [NORTH, EAST, SOUTH, WEST]
        current_index = rotations.index(current_dir)
        new_index = rotations.index(new_dir)

        # Calculate the difference in indices
        diff = new_index - current_index

        # If diff is negative or greater than 2, choose the shorter rotation path
        if diff == 1 or diff == -3:
            self.command_stack.append(cmd.Left())
        elif diff == -1 or diff == 3:
            self.command_stack.append(cmd.Right())
        elif abs(diff) == 2:
            self.command_stack.append(cmd.Right())
            self.command_stack.append(cmd.Right())

    def go_to_a_point(self, player_info: PlayerInfo, point: tuple[int, int], map_size: tuple[int, int]) -> None:
        """
        Go to a specific point
        """
        def cross_the_map(pos: int, dest: int, max: int, sup: bool) -> bool:
            if (not sup):
                return ((pos + 1) + max - dest < dest - pos)
            else :
                return (max - (pos-1) + dest <  pos - dest)
            
        def find_path(pos: int, dest: int, max: int, crossed: bool, sup: bool) -> None:
            """
            Find the path to go from pos to dest
            """
            while (pos != dest):
                self.command_stack.append(cmd.Forward())
                if crossed:
                    if sup:
                        pos = (pos + 1) % max
                    else:
                        pos = (pos - 1) % max
                if not crossed:
                    if sup:
                        pos = (pos - 1) % max
                    else:
                        pos = (pos + 1) % max
            
        pos_copy = player_info.pos
        orientiation_copy = player_info.orientation
        if player_info.pos == point:
            return
        sup: bool | None = None
        if player_info.pos[0] < point[0]:
            sup = False
        if player_info.pos[0] > point[0]:
            sup = True
        if sup != None:
            crossed = cross_the_map(pos_copy[0], point[0], map_size[0], sup)
            if bool(crossed) != bool(sup):
                self.turn(player_info.orientation, NORTH)
                orientiation_copy = NORTH
            else:
                self.turn(player_info.orientation, SOUTH)
                orientiation_copy = SOUTH
            
            find_path(pos_copy[0], point[0], map_size[0], crossed, sup)
            
        sup: bool | None = None
        if player_info.pos[1] < point[1]:
            sup = False
        if player_info.pos[1] > point[1]:
            sup = True
        if sup != None:
            crossed = cross_the_map(pos_copy[1], point[1], map_size[1], sup)
            if bool(crossed) != bool(sup):
                self.turn(orientiation_copy, EAST)
            else:
                self.turn(orientiation_copy, WEST)
                orientiation_copy = WEST
            find_path(pos_copy[1], point[1], map_size[1], crossed, sup)

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
        
        if not (0 < direction < 9):
            print("ALERT: somethin went really wrong with the direction")
            self.command_stack.append(cmd.ConnectNbr()) # Instant Command, useful for waiting
            return
                    
        if direction in [3, 4]:
            self.command_stack.append(cmd.Left())
        
        if direction in [7, 8]:
            self.command_stack.append(cmd.Right())
        
        if direction in [5, 6]:
            self.command_stack.append(cmd.Right())
            self.command_stack.append(cmd.Right())

        self.command_stack.append(cmd.Forward())

    def enough_ressources_to_incant(self, player_info: PlayerInfo, map: Map) -> bool:
        """
        Check if the player is ready to incant in terms of ressources in his inv and on the tile
        """
        current_tile: TileContent = map.tiles[player_info.pos[0]][player_info.pos[1]]
        total_rocks: Collectibles = current_tile.collectibles + player_info.inv
        enough_rocks: bool = total_rocks >= LEVEL_UP_REQ[player_info.level].collectibles
        return enough_rocks and player_info.inv.food >= 6

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
    
    
    def easy_evolve(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Try to evolve to the next level if the requirements are met
        !!! ASSUMES THAT THE PLAYERS ARE THE SAME LEVEL !!!
        """
        current_tile: TileContent = map.tiles[player_info.pos[0]][player_info.pos[1]]
        enough_players: bool = current_tile.nb_players >= LEVEL_UP_REQ[player_info.level].nb_players
        total_rocks: Collectibles = current_tile.collectibles + player_info.inv
        enough_rocks: bool = total_rocks >= LEVEL_UP_REQ[player_info.level].collectibles

        if enough_players and enough_rocks and player_info.inv.food >= 4:
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
        self.rocks_set = False

    def new_behavior(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> ABehavior:
        """
        Check if the player should switch to another behavior
        """
        if (player_info.inv.food < 3 or self.reset) and self.command_stack == []:
            return player_info.old_behavior
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
        """
        Generate the command stack for the IncantationLeader behavior
        """
        super().refresh_inventory(10)
        if not self.rocks_set:
            self.set_missing_rocks(player_info, map)
            self.rocks_set = True
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
                sender_uuid=player_info.uuid,
                sender_level=player_info.level,
                target_uuid=""
            )))))

        if len(self.players_ready_to_level_up) >= LEVEL_UP_REQ[player_info.level].nb_players:
            self.reset = True
            self.command_stack.append(cmd.Broadcast(dumps(vars(MessageContent(
                message_type=MessageContent.MessageType.LEADER_LAUCHING_INCANTATION,
                sender_uuid=player_info.uuid,
                sender_level=player_info.level,
                target_uuid=""
            )))))
        self.command_stack.append(cmd.Incantation())
        self.command_stack.append(cmd.Broadcast(dumps(vars(MessageContent(
            message_type=MessageContent.MessageType.LEADER_READY_FOR_INCANTATION,
            sender_uuid=player_info.uuid,
            sender_level=player_info.level,
            target_uuid=""
        )))))

class IncantationFollower(ABehavior):
    class State(Enum):
        """
        Enum for the state of the IncantationFollower
        """
        MOVING = 0
        WAITING = 1
        ARRIVED = 2
        ABANDONED = 3
        FINISHED = 4

    def __init__(self):
        """
        IncantationFollower behavior, the player is a follower of the incantation
        """
        super().__init__()
        self.state: IncantationFollower.State = IncantationFollower.State.MOVING
        self.destination_direction: int = 0
        self.starting_level: int = 0
        self.leader_uuid: str = ""

    def new_behavior(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> ABehavior:
        if self.state in [IncantationFollower.State.ABANDONED, IncantationFollower.State.FINISHED]:
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
            for i in range(1, len(new_messages) + 1):
                mess = new_messages[-i]
                mess_content = mess.message_content
                if mess_content == None:
                    continue
                if (mess_content.sender_level == player_info.level
                    and mess_content.message_type == MessageContent.MessageType.LEADER_READY_FOR_INCANTATION):
                    self.leader_uuid = mess_content.sender_uuid if self.leader_uuid == "" else self.leader_uuid
                    if mess_content.sender_uuid == self.leader_uuid:
                        self.destination_direction = mess.sender_direction
                        return True if mess.sender_direction == 0 else False
                    else:
                        continue
            
        def leader_abandoned() -> bool:
            """
            Check if the leader abandoned the incantation
            """
            if self.leader_uuid == "":
                return False
            for message in new_messages:
                mess_content = message.message_content
                if mess_content == None:
                    continue
                if (mess_content.sender_uuid == self.leader_uuid
                    and mess_content.message_type == MessageContent.MessageType.LEADER_ABANDONED_INCANTATION):
                    return True
            return False

        self.starting_level = player_info.level if self.starting_level == 0 else self.starting_level

        if self.starting_level != player_info.level or leader_abandoned() :
            self.state = IncantationFollower.State.FINISHED
        elif player_info.inv.food < 4:
            self.state = IncantationFollower.State.ABANDONED
        elif check_position():
            self.state = IncantationFollower.State.ARRIVED

        match self.state:
            case IncantationFollower.State.MOVING: super().go_to_direction(self.destination_direction)
            case IncantationFollower.State.WAITING:
                if not check_position(): super().go_to_direction(self.destination_direction)
                self.command_stack.append(cmd.ConnectNbr())
            case IncantationFollower.State.ARRIVED:
                self.command_stack.append(cmd.Broadcast(dumps(vars(MessageContent(
                    message_type=MessageContent.MessageType.FOLLOWER_READY_FOR_INCANTATION,
                    sender_uuid=player_info.uuid,
                    sender_level=player_info.level,
                    target_uuid=self.leader_uuid
                )))))
                self.state = IncantationFollower.State.WAITING
            case IncantationFollower.State.ABANDONED:
                self.command_stack.append(cmd.Broadcast(dumps(vars(MessageContent(
                    message_type=MessageContent.MessageType.FOLLOWER_ABANDONED_INCANTATION,
                    sender_uuid=player_info.uuid,
                    sender_level=player_info.level,
                    target_uuid=self.leader_uuid
                )))))
            case IncantationFollower.State.FINISHED: self.command_stack.append(cmd.Inventory()); return
        super().refresh_inventory(5)

class Harvester(ABehavior):
    def __init__(self):
        """
        Harvester behavior, take all ressouces he find on map
        """
        super().__init__()

    def go_to_ressources(self, player_info: PlayerInfo, map: Map):
        """
        Go to the nearest ressources
        """
        def find_nearest_resource(player_pos: tuple[int, int], tiles: List[List[TileContent]]) -> tuple[str, tuple[int, int]]:
            """
            Trouve la ressource la plus proche à partir de la position du joueur.
            Retourne le type de la ressource et sa position.
            """
            max_row = len(tiles)
            max_col = len(tiles[0]) if max_row > 0 else 0

            def distance(pos1: tuple[int, int], pos2: tuple[int, int], max_row: int, max_col: int) -> int:
                dx = abs(pos1[0] - pos2[0])
                dy = abs(pos1[1] - pos2[1])

                dx = min(dx, max_row - dx)  # Take into account wrapping on the x-axis
                dy = min(dy, max_col - dy)  # Take into account wrapping on the y-axis

                return dx + dy

            nearest_resource = ""
            nearest_position = None
            min_distance = float('inf')
            nearest_resource = ""
            nearest_position = None
            for x in range(max_row):
                for y in range(max_col):
                    tile = tiles[x][y]
                    for attr, value in tile.collectibles.__dict__.items():
                        if value > 0:
                            dist = distance(player_pos, (x, y), max_row, max_col)
                            if dist < min_distance:
                                min_distance = dist
                                nearest_resource = attr
                                nearest_position = (x, y)
                    y = (y + 1) % max_col
                x = (x + 1) % max_row
            
            return nearest_resource, nearest_position

        str_to_take = ""
        collectibles = map.tiles[player_info.pos[0]][player_info.pos[1]].collectibles
        for attr, value in collectibles.__dict__.items():
            if value > 0:
                str_to_take = attr
                break

        if str_to_take != "":
            self.command_stack.append(cmd.Take(str_to_take))
        else:
            str_to_take, position = find_nearest_resource(player_info.pos, map.tiles)
            if position:
                self.go_to_a_point( player_info, position, map.map_size)
            else:
                self.command_stack.append(cmd.Forward())
                self.command_stack.append(cmd.Look())

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
        """
        Generate the command stack for the Harvester behavior
        """
        self.go_to_ressources(player_info, map)

class Distractor(ABehavior):
    def __init__(self):
        """
        Distractor behavior, Distractor villagers that want to disturb other team
        """
        super().__init__()
        self.enemies_messages: List[str] = ["HOGRIDAAAA"]
    
    def go_to_ressources(self, player_info: PlayerInfo, map: Map):
        """
        Go to the nearest ressources
        """
        def find_nearest_resource(player_pos: tuple[int, int], tiles: List[List[TileContent]]) -> tuple[str, tuple[int, int]]:
            """
            Finds the nearest resource from the player's position.
            Returns the type of the resource and its position.
            """
            max_row = len(tiles)
            max_col = len(tiles[0]) if max_row > 0 else 0

            def distance(pos1: tuple[int, int], pos2: tuple[int, int], max_row: int, max_col: int) -> int:
                dx = abs(pos1[0] - pos2[0])
                dy = abs(pos1[1] - pos2[1])

                dx = min(dx, max_row - dx)  # Take into account wrapping on the x-axis
                dy = min(dy, max_col - dy)  # Take into account wrapping on the y-axis

                return dx + dy

            nearest_resource = ""
            nearest_position = None
            min_distance = float('inf')
            nearest_resource = ""
            nearest_position = None
            for x in range(max_row):
                for y in range(max_col):
                    tile = tiles[x][y]
                    for attr, value in tile.collectibles.__dict__.items():
                        if value > 0 and attr == "food":
                            dist = distance(player_pos, (x, y), max_row, max_col)
                            if dist < min_distance:
                                min_distance = dist
                                nearest_resource = attr
                                nearest_position = (x, y)
                    y = (y + 1) % max_col
                x = (x + 1) % max_row
            
            return nearest_resource, nearest_position

        str_to_take = ""
        collectibles = map.tiles[player_info.pos[0]][player_info.pos[1]].collectibles
        for attr, value in collectibles.__dict__.items():
            if value > 0 and attr == "food":
                str_to_take = attr
                break

        if str_to_take != "":
            self.command_stack.append(cmd.Take(str_to_take))
        else:
            str_to_take, position = find_nearest_resource(player_info.pos, map.tiles)
            if position:
                self.go_to_a_point( player_info, position, map.map_size)
            else:
                self.command_stack.append(cmd.Forward())
                self.command_stack.append(cmd.Look())

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, new_messages: List[Message]) -> None:
        """
        Generate the command stack for the Distractor behavior
        """

        self.enemies_messages.extend([message.raw_content for message in new_messages if message.message_content is None and message not in self.enemies_messages])

        if len(self.enemies_messages) != 0:
            self.command_stack.append(cmd.Broadcast(self.enemies_messages[0]))
            self.enemies_messages.remove(self.enemies_messages[0])
        self.go_to_ressources(player_info, map)

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