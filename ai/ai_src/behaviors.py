import ai_src.commands as cmd
from typing import List

class ABehavior:
    def __init__(self):
        self.command_stack: List[cmd.ACommand] = []

    def get_next_command(self) -> cmd.ACommand:
        if not self.command_stack:
            self.generate_command_stack()
        return self.command_stack.pop(0)
    
    def new_behavior(self) -> str | None:
        return None

    def generate_command_stack(self) -> None:
        raise NotImplementedError("You are not supposed to override this method")

class LookingForwards(ABehavior):
    def __init__(self):
        super().__init__()

    def generate_command_stack(self) -> None:
        self.command_stack.append(cmd.Look())
        self.command_stack.append(cmd.Forward())
