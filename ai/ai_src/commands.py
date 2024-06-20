import re
from typing import List
from collections import Counter
from ai_src.data import TileContent, Collectibles

class ACommand:
    def __init__(self, name: str) -> None:
        """
        Abstract class representing a command
        Initializes the command with its name
        """
        self.name = name
    
    def dump(self) -> str:
        """
        Returns the command's name as a string
        """
        return self.name
    
    def interpret_result(self, res: str) -> dict:
        """
        Interprets the result of the command
        Raises an exception if the command failed
        """
        if (res == "ok\n"):
            return {}
        if (res == "ko\n"):
            raise Exception(f"Failed to execute command: {res}")

class Forward(ACommand):
    def __init__(self) -> None:
        super().__init__("Forward")

class Right(ACommand):
    def __init__(self) -> None:
        super().__init__("Right")

class Left(ACommand):
    def __init__(self) -> None:
        super().__init__("Left")

class Look(ACommand):
    def __init__(self) -> None:
        super().__init__("Look")

    def interpret_result(self, res: str) -> dict:
        """
        Interprets the result of the Look command
        """
        def str_to_tile(s: str) -> TileContent:
            """
            Converts a string to a TileContent object
            """
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
            vision[key] = []
            for _ in range(n):
                vision[key].append(str_to_tile(tab.pop(0)))
            n += 2
            key += 1
        return vision

class Inventory(ACommand):
    def __init__(self) -> None:
        super().__init__("Inventory")
    
    def interpret_result(self, res: str) -> dict:
        """
        Interprets the result of the Inventory command
        Returns a serialized version of the inventory class
        """
        super().interpret_result(res)
        items = re.findall(r'(\w+)\s+(\d+)', res)
        return {item: int(quantity) for item, quantity in items}

class Broadcast(ACommand):
    def __init__(self, message: str = "") -> None:
        # Remove spaces from the message as they cause a ko
        super().__init__(f"Broadcast {message.replace(' ', '')}")

class ConnectNbr(ACommand):
    def __init__(self) -> None:
        super().__init__("Connect_nbr")

    def interpret_result(self, res: str) -> int:
        """
        Interprets the result of the Connect_nbr command
        return the numner of team unsued slots
        """
        super().interpret_result(res)
        return int(res)

class Fork(ACommand):
    def __init__(self) -> None:
        super().__init__("Fork")
    
class Eject(ACommand):
    def __init__(self) -> None:
        super().__init__("Eject")

class Take(ACommand):
    def __init__(self, obj: str = "") -> None:
        super().__init__(f"Take {obj}")

class Set(ACommand):
    def __init__(self, obj: str = "") -> None:
        super().__init__(f"Set {obj}")

class Incantation(ACommand):
    def __init__(self) -> None:
        super().__init__("Incantation")
