#!/usr/bin/env python3

from src.connection_handler import ConnectionHandler
from src.config import Config
import src.commands as cmd
import sys

# Dummy script to test the use the broadcast command as a client

def main():
    conf: Config = Config()
    try:
        com_handler: ConnectionHandler = ConnectionHandler(
            port=conf.port,
            hostname=conf.machine
        )
    except Exception as e:
        print("Failed to connect to server: " + str(e))
        sys.exit(84)
    res = com_handler.receive_response()
    if (res != "WELCOME\n"):
        print("Failed to connect to server: " + res)
        sys.exit(84)
    com_handler.send_command(conf.name)
    com_handler.receive_response()
    com_handler.receive_response()
    while True:
        com_handler.send_command(cmd.Broadcast(input("To broadcast: ")).dump())
        print(com_handler.receive_response(), end="")

if __name__ == "__main__":
    main()