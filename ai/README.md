# Zappy GUI

## Description
The Zappy AI create an instance of a player, then connect to a server to make him play and try to win with his team 
the AI can take multiple behavior and change it to the best bhavior to have at the moment

The program is divided into four main parts:

* `Bot`: The central part that connects the other components and handle the main loop.
* `Behaviors`: Handle behaviors of the bot, choose action he do, handle current situation.
* `Command`: Manages Command send to change information that AI know.
* `Connection Handling`: Handle connection with server.

## Table of Contents
1. [Bot](#bot)
2. [Behaviors](#client)
3. [Connection Handling](#game-data)
4. [Manual Control](#graphics)
5. [Control with GUI](#user-input-guide)

## Features
- Except in manual or with GUI Game got no display.
- You can launch GUI to see what happens with AI.



## Bot
Core of the program, init it, launch all the other parts and manage the main loop


#### Key Functions:

- `init()`: Launch the Config class to connect with server and create other object.
- `run()`: Starts the main loop of the AI process, Update behavior, send command and server informations.
- `handle_Command_sent()`: Change current infomations following what our ia does and what server tell us.


## Behaviors
Choose and change behaviors, and handle what each behavior had to do
Bheavior are sorted in class all inherits from Abehavior

#### Key Functions:
- `generate_command_stack()`: Check the info the bot have and define his next move by adding it to a order stack.
- `get_next_command()`: Take the next command in the queue and launch generate_command_stack if there is no command in stack.
- `new_behavior()`: Queues multiple requests to be sent to the server.
- `go_to_a_point()`: give a point so the ia will go on it easily.

### Behaviors type
- `picker` : walk on map to neraset ressources to have enough to evolve
- `leader` : when ha have enough to evolve he call other people and start an incantation
- `crazy man` : repeat what other people said while taking food to not die
all the behavior come when there is an incatation where they can participate


### Connection Handling
Connect to server and communicate with him

#### Key Functions:
- `init` : launch collection with server
- `send command` : send command to server to tell what ai does
- `receive response` : receive and interpret response from commmand to server


## Manual Control
There is a Manual Behavior wich allow you to give order in terminal directly

### Features
change the basic behavior to Manual and you could be a real ai !:

#### Command
- `r` : Turn right.
  - Usage: `r`

- `l` : Turn left.
  - Usage: `l`

- `f` : Move forward.
  - Usage: `f`

- `i` : Display inventory.
  - Usage: `i`

- `t>item` : Take an item. Replace `item` with the name of the item you want to take.
  - Usage: `t>item`

- `s>item` : Set an item down. Replace `item` with the name of the item you want to set down.
  - Usage: `s>item`

- `I` : Perform an incantation.
  - Usage: `I`

- `L` : Look around.
  - Usage: `L`

- `b` : Broadcast a message.
  - Usage: `b>message` (Replace `message` with the text you want to broadcast)

##### Object
Object are :
- `food`
- `linemate`
- `deraumere`
- `sibur`
- `mendiane`
- `phiras`
- `thystame`


## Control with GUI
In folder bonus you can load the bot.py like you would launch ai.

#### Controls

- Press the arrow keys to move
- Press `t` to take an item (it will open a menu)
- Press `d` to drop an item (it will open a menu)
- Press `l` to look
- Press `e` to incantate
- Press `b` to broadcast
- Press `i` to refresh your inventory

### Pygame
The pygame library is used to make you play the little goblin



## Compilation
use MakeFile to put binary at root of the project
- `make ` you can use The command make and it will copy python file at the root of the project
- `fclean` use make fclean to remove python file from root

## Usage
if you want to launch an ia just execute
./zappy_ai -p `port of the server` -n `name of the team`
you just have to use flag to put the port of the server and the name of the team you want to connect