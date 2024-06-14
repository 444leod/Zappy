import ai_src.commands as cmd
from typing import List

class ABehavior:
    def __init__(self):
        """
        Abstract class for behaviors
        """
        self.command_stack: List[cmd.ACommand] = []

    def get_next_command(self) -> cmd.ACommand:
        """
        Get the next command to execute from the stack
        """
        if not self.command_stack:
            self.generate_command_stack()
        return self.command_stack.pop(0)
    
    def new_behavior(self) -> str | None:
        """
        Get the name of the new behavior to switch to or None if no switch is needed
        """
        return None

    def generate_command_stack(self) -> None:
        """
        Generate the command stack, should be overriden by the child class
        """
        raise NotImplementedError("You are not supposed to override this method")

class LookingForward(ABehavior):
    def __init__(self):
        """
        LookingForward behavior, dummy behavior that looks and moves forwards
        """
        super().__init__()

    def generate_command_stack(self) -> None:
        """
        Generate the command stack for the LookingForward behavior
        """
        self.command_stack.append(cmd.Look())
        self.command_stack.append(cmd.Forward())
