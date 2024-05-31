class ACommand:
    def __init__(self, name: str) -> None:
        self.name = name
    
    def dump(self) -> str:
        return self.name

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

class Inventory(ACommand):
    def __init__(self) -> None:
        super().__init__("Inventory")

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
