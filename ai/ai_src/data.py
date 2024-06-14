from dataclasses import dataclass, field
from enum import Enum
from typing import List

# class Orientation(Enum):
"""
CONST VARIABLES representing the orientation of a player
They are represented as tuples (x, y) to facilitate the computation of the new position
"""
NORTH: tuple[int, int] = (0, 1)
EAST: tuple[int, int] = (1, 0)
SOUTH: tuple[int, int] = (0, -1)
WEST: tuple[int, int] = (-1, 0)

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

@dataclass
class Collectibles():
    """
    Dataclass representing the collectibles
    """
    food: int = 0
    linemate: int = 0
    deraumere: int = 0
    sibur: int = 0
    mendiane: int = 0
    phiras: int = 0
    thystame: int = 0

    def __repr__(self) -> str:
        """
        Returns a string representation of the collectibles
        """
        return f"f{self.food}l{self.linemate}d{self.deraumere}s{self.sibur}m{self.mendiane}p{self.phiras}t{self.thystame}"
    
    def add_object_by_name(self, str_to_take : str):
        """
        Add an object to the collectibles based on its name
        """
        if hasattr(self, str_to_take):
            setattr(self, str_to_take, getattr(self, str_to_take) + 1)

    def remove_object_by_name(self, str_to_take : str):
        """
        Remove an object to the collectibles based on its name
        """
        if hasattr(self, str_to_take):
            setattr(self, str_to_take, getattr(self, str_to_take) - 1)

    def get_nbr_object_by_name(self, str_to_take : str) -> int:
        """
        Get the number of object of a certain type
        """
        if hasattr(self, str_to_take):
            return getattr(self, str_to_take)
        return 0

@dataclass
class PlayerInfo():
    """
    Dataclass representing the player's information
    """
    level: int = 1
    inv: Collectibles = field(default_factory=lambda: Collectibles(food=10))
    pos: tuple[int, int] = (0, 0)
    orientation: tuple[int, int] = NORTH

@dataclass
class TileContent():
    """
    Dataclass representing the content of a tile
    """
    collectibles: Collectibles = field(default_factory=Collectibles)
    nb_players: int = 0

    def __repr__(self) -> str:
        """
        Returns a string representation of the tile content
        """
        return f"({self.collectibles}P{self.nb_players})"

@dataclass
class Map():
    """
    Dataclass representing the map
    """
    tiles: List[List[TileContent]] = field(default_factory=list)
    map_size: tuple[int, int] = (0, 0)
    player_pos: tuple[int, int] = (0, 0)

    def vision_update(
        self,
        vision: dict[int, TileContent],
        orientation: tuple[int, int],
        player_pos: tuple[int, int]
    ) -> None:
        """
        Updates the map with the vision
        """
        max_row = len(self.tiles)
        max_col = len(self.tiles[0]) if max_row > 0 else 0

        def update_tile(pos: tuple[int, int], content: TileContent) -> None:
            """
            Updates a tile with the given content
            """
            row, col = pos
            self.tiles[row][col] = content

        if orientation == WEST or orientation == EAST:
            for key, content in vision.items():
                vision[key].reverse()

        for key, content in vision.items():
            distance = key
            for i, tile_content in enumerate(content):
                if orientation == NORTH:
                    new_pos = (player_pos[0] - distance, player_pos[1] - (distance - i))
                elif orientation == SOUTH:
                    new_pos = (player_pos[0] + distance, player_pos[1] + (distance - i))
                elif orientation == WEST:
                    new_pos = (player_pos[0] - (distance - i), player_pos[1] - distance)
                elif orientation == EAST:
                    new_pos = (player_pos[0] + (distance - i), player_pos[1] + distance)
                new_pos = (new_pos[0] % max_row, new_pos[1] % max_col)
                update_tile(new_pos, tile_content)

    def __repr__(self) -> str:
        """
        Returns a string representation of the map
        """
        res = ""
        for x, row in enumerate(self.tiles):
            for y, tile in enumerate(row):
                res += f"{bcolors.OKGREEN}{tile}{bcolors.ENDC}" if (x, y) == self.player_pos else f"{tile}"
            res += "\n"
        return res