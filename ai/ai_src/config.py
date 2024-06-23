import sys

USAGE = "USAGE: ./zappy_ai -p port -n name [-h machine] [-m manual(true/false)]"

class ArgError(Exception):
    pass

class HelpException(Exception):
    pass

class Config:
    def __init__(self) -> None:
        """
        Parses the command line arguments
        """
        argv = sys.argv
        if (len(argv) == 1):
            raise ArgError(USAGE)
        if (argv[1] == "--help"):
            raise HelpException(USAGE)
        try:
            self.port: int = int(argv[argv.index("-p") + 1])
            self.name: str = argv[argv.index("-n") + 1]
        except Exception as _:
            raise ArgError(USAGE)
        try:
            self.machine: str = argv[argv.index("-h") + 1]
        except ValueError:
            self.machine = "localhost"
        except IndexError:
            raise ArgError(USAGE)
        self.manual: bool = True if "-m" in argv else False
        if self.name == "GRAPHIC":
            raise ArgError("Name can't be 'GRAPHIC' as it's reserved for the GUI.\n" + USAGE)