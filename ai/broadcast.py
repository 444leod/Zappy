#!/usr/bin/env python3

from src.connection_handler import ConnectionHandler
from src.config import Config, HelpException, ArgError
import src.commands as cmd
import sys

# Dummy script to test the use the broadcast command as a client

def main():
    try:
        conf: Config = Config()
        com_handler: ConnectionHandler = ConnectionHandler(
            port=conf.port,
            hostname=conf.machine
        )
    except HelpException as e:
        print(str(e))
        sys.exit(0)
    except ArgError as e:
        print(str(e))
        sys.exit(84)
    except Exception as e:
        print("Failed to connect to server: " + str(e))
        sys.exit(84)
    res = com_handler.receive_response()
    if (res != "WELCOME\n"):
        print("Failed to connect to server: " + res)
        sys.exit(84)
    com_handler.send_command(conf.name)
    tmp_res = com_handler.receive_response()
    if (tmp_res == "ko\n"):
        print("Unkowned team name")
        sys.exit(84)
    com_handler.receive_response()
    while True:
        com_handler.send_command(cmd.Broadcast(input("To broadcast: ")).dump())
        print(com_handler.receive_response(), end="")

if __name__ == "__main__":
    main()