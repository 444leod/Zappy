# Server 💻

---

The role of the server is to host the game, the rules of said game are explained in the [previous page](../README.md).
In this documentation page, technical precisions will be added about the server.
You can find, here, explanations about:

- **[Usage](#usage-)**: How to use the server.
- **[Trouble-Shooting](#trouble-shooting-)**: Issues that you might encounter.
- **[Glossary](#glossary-)**: Technical terms reference.
- **[The Project](#the-project-)**: Techical informations
    - **[Stack](#stack)**: Technologies used
    - **[Connection handling](#connection-handling)**: *self-explanatory*
    - **[Commands](#commands)**: A short list of command for both AI and GUI.

---

# Usage 🧭

To see how to install and build the project. Head to the [principal documentation](../README.md).

### Overview

The usage of the server presents as follows.
```sh
./zappy_server -p <PORT> -x <WIDTH> -y <HEIGHT> -n <TEAMS...> -c <COUNT> -f <FREQUENCY>
```
The options are as follow:
| Option | Description                                  | Example          |
|--------|----------------------------------------------|-----------------:|
| `-p`   | The port that the server will work on        | `-p 25565`       |
| `-x`   | The width of the map                         | `-x 10`          |
| `-y`   | The height of the map                        | `-y 10`          |
| `-n`   | The names of the teams (separated by spaces) | `-n teamA teamB` |
| `-c`   | The amount of players in a team at the start | `-c 5`           |
| `-f`   | The speed at which the server runs.          | `-f 2`           |

Each and every option present in this table are mandatory.

### More

Once the server starts, the game beggins, and the server start waiting for connections and commands.
You can use the ***`dev-mode`*** to see what's happening real time and get further information.
Do enter ***`dev-mode`***, simply build using:
```sh
make dev
```
And run as aforementionned, more information regarding the state of the game and the actions of the server will appear.

---

# Trouble-Shooting 🎯

Here will be explained a few of the common issues and how to fix them.

- #### Address already in use
    > "The server is not starting. The address is already in use..."

    This happens when you're attempting to start the server on a port that is in-use.
    Try changing the port number. It is also recommended to use a port in the range going **from 1024 to 65535**, as other are well-known ports most often reserved by your machine.

- #### Bad Parameters
    If you are unsure about the argument and the error is not explicit enough, simply refer to the [usage section](#usage-) above.

- #### Crashes
    This **should not happen**, it may be due to your own machine. If the issue persist and your are unable to play correctly, create an [Issue](https://github.com/444leod/Zappy/issues) on the GitHub page. Detail your issue and steps to reproduce it.

---

# Glossary 🔍

In this documentation, many technical terms will be used. To clarify and give insight as to what they mean, a glossary is provided:

- #### Server
    A program able to receive [commands](#command) from [clients](#client) and giving them [responses](#response). Its goal is to centralise the main process, here the game, in order to have a single instance run on its own and let clients act as peripherals.

- #### Client
    A program meant to discuss with the [server](#server) like a peripheral. It will acquire data through [commands](#command) and [responses](#response).
    It's main goal here is to represent either a [GUI](#gui) or an [AI](#ai).

- #### Command
    A request, in the format of a message, sent by a [client](#client) to a [server](#server). The server processes commands and picks a [response](#response) accordingly to its logic and state.

- #### Response
    A message sent by the [server](#server) to a [client](#client) with the information requested in the [command](#command) previously sent by the client.

- #### GUI
    A type of [client](#client), it is meant to give a live visibilty over the state of the current game ran by a [server](#server). It is destined to users who want to track the game and watch it play live.

- #### AI
    A type of [client](#client) meant to control a unique player. It's purpose is to play the game on its own.

- #### Player
    The actors of the game. They are meant controlled by [AIs](#ai). Each player has it's own team.

- #### Team
    Each player is part of a team. Players must cooperate to make their team win.
    A team has a name, but the team-name `GRAPHIC` is reserved for [GUIs](#gui). At the start of the game, a maximum amount of player slots is defined (see [Usage](#usage-)).

---

# The Project 📡

## Stack

- #### Language
    The server was entirely built using **C**.
    **C** is a simple compiled and low-level language. It is known for letting the memory management as a task for developper, making it very memory efficient and fast.
    Its simple set of instruction and vast amount of libraries allows it to compile extremly well to machine code making it balzingly fast.


## Connection handling

- #### Sockets
    For the program to be able to communicate to other processes and machines, we used **Unix Sockets** which is a very simple way of viewing networking.
    A [client](#client) simply plugs into a **socket** allowing it to send data directly to the server through it.

- #### Auth
    For a [client](#client) to start communicating. It needs to **authenticate**. For this, it sends which [team](#team) it will join. If it's `GRAPHIC` then it will be treated as a [GUI](#gui) (see [GUI commands](#gui-commands)); if it's one of the team names given as paramaters (see [Usage](#usage-)), then it will be associated to a new player of said team if there is enough room.

## Commands

The importance of this part is crucial for a deeper dive in the project sources.

### AI Commands

Here are all the ai commands with what the server is expected to reply.
This is not an extensive, deep-dive, complex explanation of each behaviour.
The number floating next to the command name (g.e. `7f`), is the command execution time. Some command will take longer before being processed than others, for example, moving is faster than laying an egg, naturaly.

- #### Forward `7f`
    Moves the player forward.
    Responds `ok` on success.
- #### Left `7f`
    Turns the player on its left (90° turn).
    Responds `ok` on success.
    Takes `7` time units.
- #### Right `7f`
    Turns the player on its left (90° turn).
    Responds `ok` on success.
- #### Look `7f`
    Let's the player visualise the objects and players in front of them. Players can see further by leveling-up.
    Responds with an array of objects.
- #### Take `7f`
    Given as argument the ressource name to pick up, picks up the ressource from the ground to the player's inventory.
    Responds with `ok` on success. `ko` when the ressource doesn't exist here.
- #### Set `7f`
    Given as argument the ressource name to set down, sets down the ressource on the ground from the player inventory.
    Responds with `ok` on success. `ko` when the ressource doesn't exist in the player's inventory.
- #### Inventory `1f`
    Allows players to see what's on their inventory.
    Responds with an array of ressources and their respective quantity.
- #### Fork `40f`
    Allows players to lay an egg at their position. This will allow a new player to join their team at this position, increasing the team member limit by one.
    Responds with `ok` on success.
- #### Eject `7f`
    Allows the player to push every other player on it's tile. They are pushed in the pusher's forward direction. This breaks the eggs at the pusher's position.
    Responds with `ok` on success.
- #### Incantation `300f`
    Makes the player start an incantation ritual to level-up. This puts him and other players in a freezed state.
    Responds with the new player level on success. `ko` if the conditions weren't meant.

### GUI Commands

There are many messages the [GUI](#gui) can receive from the [server](#server) without any commands being inputed.
Here, will only be covered [commands](#command) the GUI sends.

- #### msz
    Gets the size of map.
    Responds with: `msz <WIDTH> <HEIGHT>`
- #### bct `<X> <Y>`
    Gets the content of a tile.
    Responds with `bct <X> <Y>` followed by the quantity of each ressource.
- #### mct
    Gets the content of the entire map
    Responds with `bct` responses corresponding to each tile.
- #### tna
    Gets the list of team names.
    Responds with `tna <NAME>` for every team name.
- #### ppo `<PLAYER #>`
    Gets the position and orientation of the player
    Responds with `ppo <#> <X> <Y> <ORIENTATION>`
- #### plv `<PLAYER #>`
    Gets the level of a player
    Responds wuth `plv <#> <LEVEL>`
- #### pin `<PLAYER #>`
    Gets the inventory content of a player.
    Responds wuth `plv <#> <X> <Y>` followed by the quantity of each ressource.

