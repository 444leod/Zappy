import sys

USAGE = "USAGE: ./zappy_ai -p port -n name -h machine"

class Config:
    def __init__(self) -> None:
        argv = sys.argv
        if (len(argv) == 1):
            print(USAGE)
            sys.exit(84)
        if (argv[1] == "--help"):
            print(USAGE)
            sys.exit(0)
        try:
            self.port: int = int(argv[argv.index("-p") + 1])
            self.name: str = argv[argv.index("-n") + 1]
        except Exception as _:
            print(USAGE)
            sys.exit(84)
        try:
            self.machine: str = argv[argv.index("-h") + 1]
        except ValueError:
            self.machine = "localhost"
        except IndexError:
            print(USAGE)
            sys.exit(84)
        if (self.name == "GRAPHIC"):
            print("Name can't be 'GRAPHIC' as it's reserved for the GUI.")
            print(USAGE)
            sys.exit(84)