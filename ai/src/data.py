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

    def __repr__(self) -> str:
        res = ""
        for row in self.tiles:
            res += f"{row}\n"
        return res