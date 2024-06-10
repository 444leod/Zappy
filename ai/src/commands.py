import re
from typing import List
from collections import Counter
from data import TileContent, Collectibles

class ACommand:
    def __init__(self, name: str) -> None:
        self.name = name
    
    def dump(self) -> str:
        return self.name
    
    def interpret_result(self, res: str) -> dict:
        if (res == "ok\n"):
            return {}
        if (res == "ko\n"):
            raise Exception(f"Failed to execute command: {res}")

class Forward(ACommand):
    def __init__(self) -> None:
        super().__init__("Forward")
    
    #TODO: interpret_result to change player pos

class Right(ACommand):
    def __init__(self) -> None:
        super().__init__("Right")

    #TODO: interpret_result to change player orientation

class Left(ACommand):
    def __init__(self) -> None:
        super().__init__("Left")
    
    #TODO: interpret_result to change player orientation

class Look(ACommand):
    def __init__(self) -> None:
        super().__init__("Look")
    
    def interpret_result(self, res: str) -> dict:
        def str_to_tile(s: str) -> TileContent:
            items = s.split()
            counter = Counter(items)
            
            collectibles = Collectibles(
                food=counter['food'],
                linemate=counter['linemate'],
                deraumere=counter['deraumere'],
                sibur=counter['sibur'],
                mendiane=counter['mendiane'],
                phiras=counter['phiras'],
                thystame=counter['thystame']
            )
            
            nb_players = counter['player']
            
            return TileContent(collectibles=collectibles, nb_players=nb_players)

        super().interpret_result(res)
        tab: List[str] = res.strip().removeprefix('[').removesuffix(']').split(',')
        vision: dict[str, TileContent] = {}
        n: int = 1
        key: int = 0
        while tab:
            vision[str(key)] = []
            for _ in range(n):
                vision[str(key)].append(str_to_tile(tab.pop(0)))
            n += 2
            key += 1
        #!!! THE REVERSE TRICK
        for key, _ in vision.items():
            vision[key].reverse()
        return vision

class Inventory(ACommand):
    def __init__(self) -> None:
        super().__init__("Inventory")
    
    def interpret_result(self, res: str) -> dict:
        super().interpret_result(res)
        items = re.findall(r'(\w+)\s+(\d+)', res)
        return {item: int(quantity) for item, quantity in items}

class Broadcast(ACommand):
    def __init__(self, message: str) -> None:
        super().__init__(f"Broadcast {message}")

class ConnectNbr(ACommand):
    def __init__(self) -> None:
        super().__init__("Connect_nbr")
    
    #TODO: interpret_result to change nb_eggs

class Fork(ACommand):
    def __init__(self) -> None:
        super().__init("Fork")
    
    #TODO: interpret_result to change nb_eggs

class Eject(ACommand):
    def __init__(self) -> None:
        super().__init__("Eject")

class Take(ACommand):
    def __init__(self, obj) -> None:
        super().__init(f"Take {obj}")
    
    #TODO: interpret_result to change player inv and tilecontent

class Set(ACommand):
    def __init__(self, obj) -> None:
        super().__init(f"Set {obj}")
    
    #TODO: interpret_result to change player inv and tilecontent

class Incantation(ACommand):
    def __init__(self) -> None:
        super().__init("Incantation")
    
    #TODO: interpret_result to change player level