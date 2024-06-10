from dataclasses import dataclass, field
from enum import Enum
from typing import List

class Orientation(Enum):
    NORTH = 1
    EAST = 2
    SOUTH = 3
    WEST = 4

@dataclass
class Collectibles():
    food: int = 0
    linemate: int = 0
    deraumere: int = 0
    sibur: int = 0
    mendiane: int = 0
    phiras: int = 0
    thystame: int = 0

    def __repr__(self) -> str:
        return f"f{self.food}l{self.linemate}d{self.deraumere}s{self.sibur}m{self.mendiane}p{self.phiras}t{self.thystame}"

@dataclass
class PlayerInfo():
    level: int = 1
    inv: Collectibles = field(default_factory=lambda: Collectibles(food=10))
    pos: tuple[int, int] = (0, 0)
    orientation: Orientation = Orientation.NORTH

@dataclass
class GeneralInfo():
    map_size: tuple[int, int] = (0, 0)
    nb_eggs: int = 0

@dataclass
class TileContent():
    collectibles: Collectibles = field(default_factory=Collectibles)
    nb_players: int = 0

    def __repr__(self) -> str:
        return f"({self.collectibles}P{self.nb_players})"

@dataclass
class Map():
    tiles: List[List[TileContent]] = field(default_factory=list)


    #vision = {'0': {'0': [TileContent], '1': [TileContent, TileContent, TileContent]}[TileContent], '1': [TileContent, TileContent, TileContent]}
    def vision_update(
        self,
        vision: dict[str, TileContent],
        orientation: Orientation,
        player_pos: tuple[int, int]
    ) -> None:
        max_row = len(self.tiles)
        max_col = len(self.tiles[0]) if max_row > 0 else 0

        def update_tile(pos: tuple[int, int], content: TileContent) -> None:
            row, col = pos
            self.tiles[row][col] = content

        if orientation == Orientation.WEST or orientation == Orientation.EAST:
            for key, content in vision.items():
                vision[key].reverse()

        for key, content in vision.items():
            distance = int(key)
            for i, tile_content in enumerate(content): #ALL INPUT IS REVERSED
                if orientation == Orientation.NORTH: #Works by subject standard
                    new_pos = (player_pos[0] - distance, player_pos[1] - (distance - i))
                elif orientation == Orientation.SOUTH: #Works by subject standard
                    new_pos = (player_pos[0] + distance, player_pos[1] + (distance - i))
                elif orientation == Orientation.WEST: #Does not work by subject standard
                    new_pos = (player_pos[0] - (distance - i), player_pos[1] - distance)
                elif orientation == Orientation.EAST: #Does not work by subject standard
                    new_pos = (player_pos[0] + (distance - i), player_pos[1] + distance)
                new_pos = (new_pos[0] % max_row, new_pos[1] % max_col)
                update_tile(new_pos, tile_content)

    def __repr__(self) -> str:
        res = ""
        for row in self.tiles:
            res += f"{row}\n"
        return res