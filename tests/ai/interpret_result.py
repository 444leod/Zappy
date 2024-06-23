#!/usr/bin/env python3

import subprocess
import os
import ai_src.commands as cmd


res: dict = cmd.Inventory().interpret_result("[food 1 linemate 2 deraumere 3 sibur 4 mendiane 5 phiras 6 thystame 7]\n")
print(res)
