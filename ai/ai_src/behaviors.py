import ai_src.commands as cmd
from typing import List
from ai_src.data import PlayerInfo, Map

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