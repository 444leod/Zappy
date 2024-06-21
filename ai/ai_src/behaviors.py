import ai_src.commands as cmd
from typing import List
from ai_src.data import PlayerInfo, Map, Collectibles, TileContent, LEVEL_UP_REQ, TileContent
import time

NORTH: tuple[int, int] = (-1, 0)
EAST: tuple[int, int] = (0, -1)
SOUTH: tuple[int, int] = (1, 0)
WEST: tuple[int, int] = (0, 1)

NORTH: tuple[int, int] = (-1, 0)
EAST: tuple[int, int] = (0, -1)
SOUTH: tuple[int, int] = (1, 0)
WEST: tuple[int, int] = (0, 1)

class ABehavior:
    def __init__(self):
        """
        Abstract class for behaviors
        """
        self.command_stack: List[cmd.ACommand] = []

    def get_next_command(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> cmd.ACommand:
        """
        Get the next command to execute from the stack
        """
        if not self.command_stack:
            self.generate_command_stack(player_info, map, messages)
        return self.command_stack.pop(0)
    
    def new_behavior(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> str | None:
        """
        Get the name of the new behavior to switch to or None if no switch is needed
        """
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
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

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate the command stack for the LookingForward behavior
        """
        super().collect_food(player_info, map)
        super().easy_evolve(player_info, map)
        super().collect_all_rocks(player_info, map)
        self.command_stack.append(cmd.Look())
        self.command_stack.append(cmd.Forward())

class TalkingWalker(ABehavior):
    def __init__(self):
        """
        TalkingWalker behavior, dummy behavior that talks and moves
        """
        super().__init__()

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate the command stack for the TalkingWalker behavior
        """
        self.command_stack.append(cmd.Broadcast("Hello"))
        self.command_stack.append(cmd.Forward())
        self.command_stack.append(cmd.Forward())
        self.command_stack.append(cmd.Right())



class Greg(ABehavior):
    def __init__(self):
        """
        Greg behavior, take all ressouces he find on map
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
            
            
        
    def generate_command_stack(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Generate the command stack for the Greg behavior
        """
        self.go_to_ressources(player_info, map)

class Eric(ABehavior):
    def __init__(self):
        """
        Eric behavior, Crazy villagers that want to disturb other team
        """
        super().__init__()
        self.messages_received: List[str] = []
        self.team_message: List[str] = ["HOGRIDAAAA", "HELLO"]
    
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

    def generate_command_stack(self, player_info: PlayerInfo, map: Map, messages: List[tuple[int, str]]) -> None:
        """
        Generate the command stack for the Eric behavior
        """
        def is_team_message(message: str) -> bool:
            """
            Ignore the team message
            """
            message = message.replace(" ", "")
            message = message.replace("\n", "")
            return message in self.team_message
        def sort_messages(messages: List[tuple[int, str]]) -> None:
            """
            Sort the messages so eric don't always say the same
            """
            if len(messages) == 0:
                return
            for message in messages:
                if message[1] not in self.messages_received and not is_team_message(message[1]):
                    message = list(message)
                    message[1] = message[1].replace(" ", "")
                    message[1] = message[1].replace("\n", "")
                    self.messages_received.append(message[1])
                    return
        sort_messages(messages)
        if len(self.messages_received) != 0:
            self.command_stack.append(cmd.Broadcast(self.messages_received[0]))
            self.messages_received.remove(self.messages_received[0])
        self.go_to_ressources(player_info, map)



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