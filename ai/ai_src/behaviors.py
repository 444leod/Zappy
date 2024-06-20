import ai_src.commands as cmd
from typing import List
from ai_src.data import PlayerInfo, Map, TileContent
import time

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

            
        pos_copy = player_info.pos
        orientiation_copy = player_info.orientation
        print("pos_copy before:", pos_copy)
        print("player info pos before:", player_info.pos)
        print("point:", point)
        if player_info.pos == point:
            return
        sup: bool | None = None
        if player_info.pos[0] < point[0]:
            sup = False
        if player_info.pos[0] > point[0]:
            sup = True
        if sup != None:
            crossed = cross_the_map(pos_copy[0], point[0], map_size[0], sup)
            print("crossed:", crossed)
            print("sup:", sup)
            print("map_size[0]:", map_size[0])
            if bool(crossed) != bool(sup):
                self.turn(player_info.orientation, NORTH)
                orientiation_copy = NORTH
                print("turn north")
            else:
                self.turn(player_info.orientation, SOUTH)
                orientiation_copy = SOUTH
                print("turn south")
            
            while pos_copy [0] != point[0]:
                print("move on y")
                self.command_stack.append(cmd.Forward())
                if crossed:
                    if sup:
                        pos_copy = (pos_copy[0] + 1, pos_copy[1])
                        if pos_copy[0] >= map_size[0]:
                            pos_copy = (0, pos_copy[1])
                    else:
                        pos_copy = (pos_copy[0] - 1, pos_copy[1])
                        if pos_copy[0] < 0:
                            pos_copy = (map_size[0] - 1, pos_copy[1])
                if not crossed:
                    if sup:
                        pos_copy = (pos_copy[0] - 1, pos_copy[1])
                    else:
                        pos_copy = (pos_copy[0] + 1, pos_copy[1])
            
        sup: bool | None = None
        if player_info.pos[1] < point[1]:
            sup = False
        if player_info.pos[1] > point[1]:
            sup = True
        print("sup:", sup)
        if sup != None:
            crossed = cross_the_map(pos_copy[1], point[1], map_size[1], sup)
            if bool(crossed) != bool(sup):
                self.turn(orientiation_copy, EAST)
                print("turn east")
            else:
                self.turn(orientiation_copy, WEST)
                orientiation_copy = WEST
                print("turn west")
            while pos_copy [1] != point[1]:
                self.command_stack.append(cmd.Forward())
                print("move on x")
                if crossed:
                    if sup:
                        pos_copy = (pos_copy[0], pos_copy[1] + 1)
                        if pos_copy[1] >= map_size[1]:
                            pos_copy = (pos_copy[0], 0)
                    else:
                        pos_copy = (pos_copy[0], pos_copy[1] - 1)
                        if pos_copy[1] < 0:
                            pos_copy = (pos_copy[0], map_size[1] - 1)
                if not crossed:
                    if sup:
                        pos_copy = (pos_copy[0], pos_copy[1] - 1)
                    else:
                        pos_copy = (pos_copy[0], pos_copy[1] + 1)
        

    

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
                            print("value:", value)
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
            print("no ressources to take")
            str_to_take, position = find_nearest_resource(player_info.pos, map.tiles)
            if position:
                print("position:", position)
                print("nearest ressource:", str_to_take)
                self.go_to_a_point( player_info, position, map.map_size)
                self.collect_all_on_tiles(position, map)
            else:
                self.command_stack.append(cmd.Forward())
                self.command_stack.append(cmd.Look())
            
            
        
    def generate_command_stack(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Generate the command stack for the Greg behavior
        """
        print("\nplayer info pos:", player_info.pos)
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