import sys

USAGE = "USAGE: ./zappy_ai -p port -n name -h machine"

class ArgError(Exception):
    pass

class HelpException(Exception):
    pass

class Config:
    def __init__(self) -> None:
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
            ArgError(USAGE)
        if (self.name == "GRAPHIC"):
            ArgError("Name can't be 'GRAPHIC' as it's reserved for the GUI.\n" + USAGE)