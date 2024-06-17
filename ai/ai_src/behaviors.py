import ai_src.commands as cmd
from typing import List
from ai_src.data import PlayerInfo, Map, TileContent

NORTH: tuple[int, int] = (0, 1)
EAST: tuple[int, int] = (1, 0)
SOUTH: tuple[int, int] = (0, -1)
WEST: tuple[int, int] = (-1, 0)

class ABehavior:
    def __init__(self):
        """
        Abstract class for behaviors
        """
        self.command_stack: List[cmd.ACommand] = []

    def get_next_command(self, player_info: PlayerInfo, map: Map) -> cmd.ACommand:
        """
        Get the next command to execute from the stack
        """
        if not self.command_stack:
            self.generate_command_stack(player_info, map)
        return self.command_stack.pop(0)
    
    def new_behavior(self, player_info: PlayerInfo, map: Map) -> str | None:
        """
        Get the name of the new behavior to switch to or None if no switch is needed
        """
        return None

    def generate_command_stack(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Generate the command stack, should be overriden by the child class
        """
        raise NotImplementedError("You are not supposed to override this method")
    
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
            self.command_stack.append(cmd.Right())
        elif diff == -1 or diff == 3:
            self.command_stack.append(cmd.Left())
        elif abs(diff) == 2:
            self.command_stack.append(cmd.Right())
            self.command_stack.append(cmd.Right())

    def go_to_a_point(self, player_info: PlayerInfo, point: tuple[int, int]) -> None:
        """
        Go to a specific point
        """
        pos_copy = player_info.pos
        if player_info.pos == point:
            return
        if player_info.pos[0] < point[0]:
            self.turn(player_info.orientation, EAST)
            while pos_copy [0] < point[0]:
                self.command_stack.append(cmd.Forward())
                pos_copy = (pos_copy[0] + 1, pos_copy[1])
        elif player_info.pos[0] > point[0]:
            self.turn(player_info.orientation, WEST)
            while pos_copy [0] > point[0]:
                self.command_stack.append(cmd.Forward())
                pos_copy = (pos_copy[0] - 1, pos_copy[1])
        if player_info.pos[1] < point[1]:
            self.turn(player_info.orientation, NORTH)
            while pos_copy [1] < point[1]:
                self.command_stack.append(cmd.Forward())
                pos_copy = (pos_copy[0], pos_copy[1] + 1)
        elif player_info.pos[1] > point[1]:
            self.turn(player_info.orientation, SOUTH)
            while pos_copy [1] > point[1]:
                self.command_stack.append(cmd.Forward())
                pos_copy = (pos_copy[0], pos_copy[1] - 1)

    

class LookingForward(ABehavior):
    def __init__(self):
        """
        LookingForward behavior, dummy behavior that looks and moves forwards
        """
        super().__init__()

    def generate_command_stack(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Generate the command stack for the LookingForward behavior
        """
        self.command_stack.append(cmd.Look())
        self.command_stack.append(cmd.Forward())

class TalkingWalker(ABehavior):
    def __init__(self):
        """
        TalkingWalker behavior, dummy behavior that talks and moves
        """
        super().__init__()

    def generate_command_stack(self,  player_info: PlayerInfo, map: Map) -> None:
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

            def distance(pos1: tuple[int, int], pos2: tuple[int, int]) -> int:
                return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1])

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
                            dist = distance(player_pos, (x, y))
                            if dist < min_distance:
                                min_distance = dist
                                nearest_resource = attr
                                nearest_position = (x, y)
            
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
            print("position: ", str_to_take, position)
            if position:
                self.go_to_a_point( player_info, position)
            
            
        
    def generate_command_stack(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Generate the command stack for the Greg behavior
        """
        self.command_stack.append(cmd.Look())
        self.go_to_ressources(player_info, map)

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

            def distance(pos1: tuple[int, int], pos2: tuple[int, int]) -> int:
                return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1])

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
                            dist = distance(player_pos, (x, y))
                            if dist < min_distance:
                                min_distance = dist
                                nearest_resource = attr
                                nearest_position = (x, y)
            
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
            print("position: ", str_to_take, position)
            if position:
                self.go_to_a_point( player_info, position)
            
            
        
    def generate_command_stack(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Generate the command stack for the Greg behavior
        """
        self.command_stack.append(cmd.Look())
        self.go_to_ressources(player_info, map)

class Manual(ABehavior):
    def __init__(self):
        """
        Manual behavior, the player is controlled by the user
        """
        super().__init__()
        print("r for right, l for left, f for forward, i for inventory, t>item for take, s>item for set, I for incantation, L for look")

    def generate_command_stack(self,  player_info: PlayerInfo, map: Map) -> None:
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
        
        self.command_stack.append(cmd_to_send)