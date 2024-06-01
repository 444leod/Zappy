import re

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
        super().interpret_result(res)

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

class Fork(ACommand):
    def __init__(self) -> None:
        super().__init("Fork")

class Eject(ACommand):
    def __init__(self) -> None:
        super().__init__("Eject")

class Take(ACommand):
    def __init__(self, obj) -> None:
        super().__init(f"Take {obj}")

class Set(ACommand):
    def __init__(self, obj) -> None:
        super().__init(f"Set {obj}")

class Incantation(ACommand):
    def __init__(self) -> None:
        super().__init("Incantation")
