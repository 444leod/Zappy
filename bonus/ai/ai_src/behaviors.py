import ai_src.commands as cmd
from typing import List
from ai_src.data import PlayerInfo, Map, TileContent
import time
import pygame
import sys
import os
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
            crossed = cross_the_map(pos_copy[0], point[0], map_size[1], sup)
            if bool(crossed) != bool(sup):
                self.turn(player_info.orientation, NORTH)
                orientiation_copy = NORTH
            else:
                self.turn(player_info.orientation, SOUTH)
                orientiation_copy = SOUTH
            
            find_path(pos_copy[0], point[0], map_size[1], crossed, sup)
            
        sup: bool | None = None
        if player_info.pos[1] < point[1]:
            sup = False
        if player_info.pos[1] > point[1]:
            sup = True
        if sup != None:
            crossed = cross_the_map(pos_copy[1], point[1], map_size[0], sup)
            if bool(crossed) != bool(sup):
                self.turn(orientiation_copy, EAST)
            else:
                self.turn(orientiation_copy, WEST)
                orientiation_copy = WEST
            find_path(pos_copy[1], point[1], map_size[0], crossed, sup)
        

    

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

class Gaming(ABehavior):
    def __init__(self, screen: pygame.Surface):
        """
        Manual behavior, the player is controlled by the user
        """
        super().__init__()
        self.screen = screen
        font_path = os.path.join(os.getcwd(), "Blockhead.ttf")
        self.font = pygame.font.Font(font_path, 20)
        self.litlle_font = pygame.font.Font(font_path, 12)

    def take_object(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Take the object on the tile
        """
        run = True
        square_size = 200
        square_x = (800 - square_size) / 2
        square_y = (600 - square_size) / 2
        pygame.draw.rect(self.screen, (0, 0, 0), (square_x, square_y, square_size, square_size))
        tiles = map.tiles
        tile = tiles[player_info.pos[0]][player_info.pos[1]]
        tab = []
        cursor = 0
        for attr, value in tile.collectibles.__dict__.items():
            if value > 0:
                tab.append(attr)
        if len(tab) == 0:
            return
        cursor = 0
        while run:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        run = False
                    if event.key == pygame.K_DOWN:
                        cursor = (cursor + 1) % len(tab)
                    if event.key == pygame.K_UP:
                        cursor = (cursor - 1) % len(tab)
                    if event.key == pygame.K_RETURN:
                        self.command_stack.append(cmd.Take(tab[cursor]))
                        run = False
            i = 0
            color = (255, 255, 255)
            for attr, value in tile.collectibles.__dict__.items():
                if value > 0:
                    if cursor == i:
                        color = (255, 0, 0)
                    text = self.font.render(f"{attr}: {value}", True, color)
                    self.screen.blit(text, (square_x, square_y + i * 25))
                    i += 1
                    color = (255, 255, 255)
            pygame.display.flip()


    def put_object(self, player_info: PlayerInfo, map: Map) -> None:
        """
        Put the object on the tile
        """
        run = True
        square_size = 200
        square_x = (800 - square_size) / 2
        square_y = (600 - square_size) / 2
        pygame.draw.rect(self.screen, (0, 0, 0), (square_x, square_y, square_size, square_size))
        tiles = map.tiles
        tile = tiles[player_info.pos[0]][player_info.pos[1]]
        tab = []
        cursor = 0
        for attr, value in player_info.inv.__dict__.items():
            if value > 0:
                tab.append(attr)
        if len(tab) == 0:
            return
        cursor = 0
        while run:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        run = False
                    if event.key == pygame.K_DOWN:
                        cursor = (cursor + 1) % len(tab)
                    if event.key == pygame.K_UP:
                        cursor = (cursor - 1) % len(tab)
                    if event.key == pygame.K_RETURN:
                        self.command_stack.append(cmd.Set(tab[cursor]))
                        run = False
            i = 0
            color = (255, 255, 255)
            for attr, value in player_info.inv.__dict__.items():
                if value > 0:
                    if cursor == i:
                        color = (255, 0, 0)
                    text = self.font.render(f"{attr}: {value}", True, color)
                    self.screen.blit(text, (square_x, square_y + i * 25))
                    i += 1
                    color = (255, 255, 255)
            pygame.display.flip()

    def broadcast(self, player_info: PlayerInfo) -> None:
        """
        Broadcast a message
        """
        run = True
        square_size = 200
        square_x = (800 - square_size) / 2
        square_y = (600 - square_size) / 2
        pygame.draw.rect(self.screen, (0, 0, 0), (square_x, square_y, square_size, square_size))
        text = self.litlle_font.render("Enter your message", True, (255, 255, 255))
        self.screen.blit(text, (square_x, square_y))
        message = ""
        while run:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        run = False
                    if event.key == pygame.K_RETURN:
                        self.command_stack.append(cmd.Broadcast(message))
                        run = False
                    if event.key == pygame.K_BACKSPACE:
                        message = message[:-1]
                    else:
                        message += event.unicode
            text = self.font.render(message, True, (255, 255, 255))
            self.screen.blit(text, (square_x, square_y + 50))
            pygame.display.flip()


    def show_inventory(self, player_info: PlayerInfo) -> None:
        """
        Show the player's inventory
        """
        run = True
        square_size_x = 150
        square_size_y = 600
        square_x = (800 - square_size_x)
        square_y = (600 - square_size_y)
        pygame.draw.rect(self.screen, (0, 0, 0), (square_x, square_y, square_size_x, square_size_y))
        text = self.litlle_font.render("Inventory", True, (255, 255, 255))
        self.screen.blit(text, (square_x, square_y))
        tab = []
        cursor = 0
        for attr, value in player_info.inv.__dict__.items():
            if value > 0:
                tab.append(attr)
        i = 1
        color = (255, 255, 255)
        for attr, value in player_info.inv.__dict__.items():
            if value > 0:
                if cursor == i:
                    color = (255, 0, 0)
                text = self.litlle_font.render(f"{attr}: {value}", True, color)
                self.screen.blit(text, (square_x, square_y + i * 25))
                i += 1
                color = (255, 255, 255)
        pygame.display.flip()

    def generate_command_stack(self,  player_info: PlayerInfo, map: Map) -> None:
        """
        Generate a command by the user
        """
        for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit(0)
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_UP:
                        self.command_stack.append(cmd.Forward())
                    if event.key == pygame.K_RIGHT:
                        self.command_stack.append(cmd.Left())
                    if event.key == pygame.K_LEFT:
                        self.command_stack.append(cmd.Right())
                    if event.key == pygame.K_DOWN:
                        self.command_stack.append(cmd.Left())
                        self.command_stack.append(cmd.Left())
                    if event.key == pygame.K_ESCAPE:
                        sys.exit(0)
                    if event.key == pygame.K_i:
                        self.show_inventory(player_info)
                        self.command_stack.append(cmd.Inventory())
                    if event.key == pygame.K_t:
                        self.take_object(player_info, map)
                    if event.key == pygame.K_d:
                        self.put_object(player_info, map)
                    if event.key == pygame.K_e:
                        self.command_stack.append(cmd.Incantation())
                    if event.key == pygame.K_b:
                        self.broadcast(player_info)
        
        if not self.command_stack:
            print("No command")
            self.command_stack.append(cmd.Look())
            self.show_inventory(player_info)
            self.command_stack.append(cmd.Inventory())
