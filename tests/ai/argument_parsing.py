#!/usr/bin/env python3

# Usage:

"USAGE: ./zappy_ai -p port -n name [-h machine] [-m]"

import subprocess
import os

SERVER_PORT = 5555
TEAM_NAME_0 = "test0"
TEAM_NAME_1 = "test1"

try:
    if os.path.isfile('./zappy_ai') == False or os.path.isfile('./zappy_server') == False:
        print("Executable not found in directory")
        exit(1)

    server_process = subprocess.Popen(["./zappy_server", "-p", f"{SERVER_PORT}", "-x", "10", "-y", "10", "-n", f"{TEAM_NAME_0}", f"{TEAM_NAME_1}", "-c", "15", "-f", "50"])

    assert (subprocess.getstatusoutput('./zappy_ai'))[0] == 84, "No arguments passed, expected return code 84"

    assert (subprocess.getstatusoutput('./zappy_ai -p'))[0] == 84, "No port passed, expected return code 84"

    assert (subprocess.getstatusoutput(f'./zappy_ai -p {SERVER_PORT}'))[0] == 84, "No name passed, expected return code 84"

    assert (subprocess.getstatusoutput(f'./zappy_ai -p {SERVER_PORT} -n'))[0] == 84, "No name passed, expected return code 84"

    assert (subprocess.getstatusoutput(f'./zappy_ai -p {SERVER_PORT} -n {TEAM_NAME_0} -h'))[0] == 84, "No machine passed, expected return code 84"

    assert (subprocess.getstatusoutput(f'./zappy_ai -p {SERVER_PORT} -n GRAPHIC'))[0] == 84, "Name is GRAPHIC, expected return code 84"

    #close server port
    os.kill(server_process.pid, 9)

    print("All tests passed")
except:
    print("Error in argument parsing test")
    exit(1)