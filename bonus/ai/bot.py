#!/usr/bin/env python3

import sys
from typing import List
from ai_src.connection_handler import ConnectionHandler
from ai_src.config import Config, HelpException, ArgError
from ai_src.data import PlayerInfo, Collectibles, Map, TileContent
from ai_src.behaviors import LookingForward, TalkingWalker, Greg, Manual, Gaming
import pygame
import ai_src.commands as cmd
import os
import random
from ai_src.utils import add_tuples, turn_left, turn_right

class Bot():
    def __init__(self, screen, verbose: bool=False, traced: bool=False) -> None:
        """
        Represents an instance of a bot playing the game
        Attributes:
            verbose: Whether to print debug messages
            traced: Whether to log debug messages to a file
        """
        try:
            self.conf: Config = Config()
            self.com_handler: ConnectionHandler = ConnectionHandler(
                port=self.conf.port,
                hostname=self.conf.machine
            )
            self.background = pygame.image.load(os.path.join(os.getcwd(), "background.png"))
            self.player = pygame.image.load(os.path.join(os.getcwd(), "goblin.png"))
            self.ressources = pygame.image.load(os.path.join(os.getcwd(), "ressources.png"))
            self.ennemies = pygame.image.load(os.path.join(os.getcwd(), "hogrider.png"))
            self.ressources_square = self.ressources.subsurface((0, 0, 16, 16))
            self.square = self.player.subsurface((0, 0, 64, 64))
            self.screen = screen
            font_path = os.path.join(os.getcwd(), "Blockhead.ttf")
            self.font = pygame.font.Font(font_path, 15)


        except HelpException as e:
            print(str(e))
            sys.exit(0)
        except ArgError as e:
            print(str(e))
            sys.exit(84)
        except Exception as e:
            print("Failed to connect to server: " + str(e))
            sys.exit(84)
        self.results: List[str] = []
        self.results.append(self.com_handler.receive_response())
        if (self.results[-1] != "WELCOME\n"):
            print("Failed to connect to server: " + self.results[-1])
            sys.exit(84)

        self.com_handler.send_command(self.conf.name)
        self.results.append(self.com_handler.receive_response())
        if (self.results[-1] == "ko\n"):
            print("Unkowned team name")
            sys.exit(84)
        self.results.append(self.com_handler.receive_response())

        self.verbose: bool = verbose
        self.traced: bool = traced
        self.nb_eggs = int(self.results[-2])

        self.player_info: PlayerInfo = PlayerInfo()

        self.map: Map = Map()
        self.map.map_size = tuple(map(int, self.results[-1].split()))
        self.map.tiles = [[TileContent() for _ in range(self.map.map_size[0])] for _ in range(self.map.map_size[1])]
        self.map.tiles[0][0].nb_players = 1

        self.messages_received: List[tuple[int, str]] = [] # [(player_direction, message), ..]
        self.messages_sent: List[str] = []
        self.cmd_sent: List[str] = []
        self.base_funcs = {
            "dead\n" : self.die,
            "message": self.receive_broadcast,
        }
        self.current_behavior = Gaming(self.screen) 

    def draw_ressources(self, x_start=0, y_start=0):
        print_x = 0
        print_y = 0
        for x in range(x_start,10 + x_start):
            for y in range(y_start,9 + y_start):
                tile = self.map.tiles[x][y]
                if tile.collectibles.food > 0:
                    self.ressources_square = self.ressources.subsurface((0, 16 * 4, 16, 16))
                    pos = ((x + 20) % 35 , (y + 5) % 40)
                    self.screen.blit(self.ressources_square, ((print_x * 64) +  pos[0], print_y * 64 + pos[1]))
                if tile.collectibles.linemate > 0:
                    self.ressources_square = self.ressources.subsurface((0, 16 * 0, 16, 16))
                    pos = ((x + 2) % 35 , (y + 25) % 40)
                    self.screen.blit(self.ressources_square, ((print_x * 64) +  pos[0], print_y * 64 + pos[1]))
                if tile.collectibles.deraumere > 0:
                    self.ressources_square = self.ressources.subsurface((0, 16 * 1, 16, 16))
                    pos = ((x + 18) % 35 , (y + 15) % 40)
                    self.screen.blit(self.ressources_square, ((print_x * 64) +  pos[0], print_y * 64 + pos[1]))
                if tile.collectibles.sibur > 0:
                    self.ressources_square = self.ressources.subsurface((0, 16 * 2, 16, 16))
                    pos = ((x + 17) % 35 , (y + 36) % 40)
                    self.screen.blit(self.ressources_square, ((print_x * 64) +  pos[0], print_y * 64 + pos[1]))
                if tile.collectibles.mendiane > 0:
                    self.ressources_square = self.ressources.subsurface((0, 16 * 3, 16, 16))
                    pos = ((x + 5) % 35 , (y + 27) % 40)
                    self.screen.blit(self.ressources_square, ((print_x * 64) +  pos[0], print_y * 64 + pos[1]))
                if tile.collectibles.phiras > 0:
                    self.ressources_square = self.ressources.subsurface((0, 16 * 5, 16, 16))
                    pos = ((x + 12) % 35 , (y + 3) % 40)
                    self.screen.blit(self.ressources_square, ((print_x * 64) +  pos[0], print_y * 64 + pos[1]))
                if tile.collectibles.thystame > 0:
                    self.ressources_square = self.ressources.subsurface((0, 16 * 6, 16, 16))
                    pos = ((x + 25) % 35 , (y + 36) % 40)
                    self.screen.blit(self.ressources_square, ((print_x * 64) +  pos[0], print_y * 64 + pos[1]))
                if tile.nb_players > 1 or tile.nb_players > 0 and self.player_info.pos != (x, y):
                    self.screen.blit(self.ennemies, (print_x * 64, print_y * 64))
                print_y += 1
            print_x += 1    
    def draw(self):
        square_y = 0
        if self.player_info.orientation == (-1, 0):
            square_y = 64 
        elif self.player_info.orientation == (1, 0):
            square_y = 64 * 2
        elif self.player_info.orientation == (0, -1):
            square_y = 64 * 3
        elif self.player_info.orientation == (0, 1):
            square_y = 0
        x_start = 11 - self.player_info.pos[0] if self.player_info.pos[0] >= 10 else 0
        y_start = 10 - self.player_info.pos[1] if self.player_info.pos[1] >= 9 else 0


        for x in range(10):
            for y in range(9):
                self.screen.blit(self.background, (x * 64, y * 64))
                if y + 1 >= self.map.map_size[1]:
                    y = 10
            if x + 1 >= self.map.map_size[0]:
                x = 10
        self.draw_ressources(x_start, y_start)
        self.square = self.player.subsurface((0, square_y, 64, 64))
        pos = self.player_info.pos
        if pos[0] >= 10:
            pos = (9, pos[1])
        if pos[1] >= 9:
            pos = (pos[0], 8)
        self.screen.blit(self.square, (pos[0] * 64, pos[1] * 64))
        square_size_x = 150
        square_x = (800 - square_size_x)
        square_y = (550)
        level = "level : " + str(self.player_info.level)
        text = self.font.render(level , True, (255, 255, 255))
        self.screen.blit(text, (square_x, square_y))
            
        
        pygame.display.flip()


    def run(self) -> None:
        """
        Main loop of the bot
        The only function that should be called from the outside
        """
        while True:
            self.log(self.map)
            self.draw()
            self.behavior_logic()
            self.receive_command()
            self.handle_commands_sent()

    def log(self, *args, **kargs) -> None:
        """
        Logs the message to stdout and to a file if tracing is enabled
        """
        if (self.verbose):
            print(*args, **kargs)
        if (self.traced):
            with open(".trace", "a") as f:
                print(*args, file=f)

    def die(self) -> None:
        """
        Handle the bot's death
        """
        self.log("Bot died. Exiting.")
        sys.exit(0)

    def receive_broadcast(self) -> None:
        """
        Handle receiving a broadcast message
        """
        tab: List[str] = self.results[-1].split(" ")
        if (len(tab) != 3) or not (tab[1][:-1].isdigit()):
            return
        self.messages_received.append((int(tab[1][:-1]), tab[2]))
    
    def level_up(self) -> None:
        """
        Handle the bot's level up via incantation
        """
        self.player_info.level += 1

    def behavior_logic(self) -> None:
        """
        Handle the bot's behavior
        """
        cmd_to_send: cmd.ACommand = self.current_behavior.get_next_command(self.player_info, self.map)
        self.log(cmd_to_send.dump())
        self.cmd_sent.append(cmd_to_send.dump())
        self.com_handler.send_command(cmd_to_send.dump())

    def receive_command(self) -> None:
        """
        Receive a command from the server
        Also handles death and broadcast messages
        """
        while True:
            # Wait for the response
            self.results.append(self.com_handler.receive_response())
            self.log(self.results[-1], end="")

            # Handle death or receiving a message by Broadcast
            key: str = self.results[-1].split(" ")[0]
            if (key in self.base_funcs):
                self.base_funcs[key]()
                continue
            # Returning to the main loop if the response is not a message or a death
            return
        
    def handle_forward(self) -> None:
        """
        Handle the forward command
        """
        self.map.tiles[self.player_info.pos[0]][self.player_info.pos[1]].nb_players -= 1
        self.player_info.pos = add_tuples(self.player_info.pos, self.player_info.orientation)
        self.player_info.pos = (self.player_info.pos[0] % self.map.map_size[0], self.player_info.pos[1] % self.map.map_size[1])
        self.log(self.player_info.pos)
        self.map.player_pos = self.player_info.pos
        self.map.tiles[self.player_info.pos[0]][self.player_info.pos[1]].nb_players += 1

    def handle_look(self) -> None:
        """
        Handle the look command
        """
        self.map.vision_update(
            cmd.Look().interpret_result(self.results[-1]),
            self.player_info.orientation,
            self.player_info.pos
        )
    
    def handle_eject(self) -> None:
        """
        Handle the eject command
        """
        try :
            cmd.Eject().interpret_result(self.results[-1])
            self.map.tiles[self.player_info.pos[0]][self.player_info.pos[1]].nb_players = 1
        except Exception:
            pass

    def handle_fork(self) -> None:
        """
        Handle the fork command
        """
        try:
            cmd.Fork().interpret_result(self.results[-1])
            self.nb_eggs += 1
        except Exception as e:
            self.log(e)
            self.log("Failed to fork")

    def handle_take(self, object: str) -> None:
        """
        Handle the take command
        """
        try:
            pos = self.player_info.pos
            cmd.Set().interpret_result(self.results[-1])
            self.player_info.inv.add_object_by_name(object)
            self.map.tiles[pos[0]][pos[1]].collectibles.remove_object_by_name(object)
            print(self.map.tiles[pos[0]][pos[1]].collectibles)
        except Exception as e:
            self.map.tiles[pos[0]][pos[1]].collectibles.remove_all_objects_by_name(object)
            self.log(e)
            self.log("Failed to take object")

    def handle_set(self, object: str) -> None:
        """
        Handle the set command
        """
        try:
            pos = self.player_info.pos
            cmd.Set().interpret_result(self.results[-1])
            self.player_info.inv.remove_object_by_name(object)
            self.map.tiles[pos[0]][pos[1]].collectibles.add_object_by_name(object)
        except Exception as e:
            self.log(e)
            self.log("Failed to set object")

    def handle_incantation(self) -> None:
        """
        Handle the incantation command
        """
        try:
            cmd.Incantation().interpret_result(self.results[-1])
            self.receive_command()
            cmd.Incantation().interpret_result(self.results[-1])
            self.player_info.level += 1
        except Exception as e:
            self.log(e)
            self.log("Failed to incant")

    def handle_commands_sent(self) -> None:
        """
        Handle the commands sent by the bot
        Loop that handles the commands sent by the bot
        """
        cmd_sent: str = self.cmd_sent[-1].split(" ")[0]
        try :
            cmd_sup: str = self.cmd_sent[-1].split(" ")[1]
        except IndexError:
            cmd_sup = ""
        match cmd_sent:
            case "Inventory": self.player_info.inv = Collectibles(**(cmd.Inventory().interpret_result(self.results[-1])))
            case "Look": self.handle_look()
            case "Forward": self.handle_forward()
            case "Right": self.player_info.orientation= turn_right(self.player_info.orientation)
            case "Left": self.player_info.orientation = turn_left(self.player_info.orientation)
            case "Broadcast": self.messages_sent.append(cmd.Broadcast().interpret_result(self.results[-1]))
            case "Connect_nbr": cmd.ConnectNbr().interpret_result(self.results[-1])
            case "Eject": self.handle_eject()
            case "Fork": self.handle_fork()
            case "Take": self.handle_take(cmd_sup)
            case "Set": self.handle_set(cmd_sup)
            case "Incantation": self.handle_incantation()



class EGame:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((800, 600))
        pygame.display.set_caption("EGame")
        self.clock = pygame.time.Clock()
        font_path = os.path.join(os.getcwd(), "Blockhead.ttf")
        self.font = pygame.font.Font(font_path, 36)
        self.background_image = pygame.image.load(os.path.join(os.getcwd(), "cr_background.png"))
        self.running = True

    def draw_text(self, text, position, color=(255, 255, 255), underline=False):
        text_surface = self.font.render(text, True, color)
        self.screen.blit(text_surface, position)
        if underline:
            text_width, text_height = self.font.size(text)
            line_thickness = 8
            underline_y_offset = 5
            start_pos = (position[0], position[1] + text_height + underline_y_offset)
            end_pos = (position[0] + text_width, position[1] + text_height + underline_y_offset)
            pygame.draw.line(self.screen, color, start_pos, end_pos, line_thickness)
    
    def main_game(self):
        Bot(self.screen).run()

    def main_screen(self):

        menu_color = [(100, 215, 0), (255, 255, 255)]
        while self.running:

            self.screen.fill((0, 0, 0))
            
            self.screen.blit(self.background_image, (287, 15))
            self.draw_text("Zappy", (330, 100), (100, 215, 0), True) 
            self.draw_text("Play", (350, 250), menu_color[0])
            self.draw_text("Quit", (350, 350), menu_color[1])

            mouse_pos = pygame.mouse.get_pos()
            if 350 < mouse_pos[0] < 450 and 250 < mouse_pos[1] < 300:
                menu_color = [(100, 215, 0), (255, 255, 255)]
            elif 350 < mouse_pos[0] < 450 and 350 < mouse_pos[1] < 400:
                menu_color = [(255, 255, 255), (100, 215, 0)]
            pygame.display.flip()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_UP or event.key == pygame.K_DOWN:
                        menu_color = menu_color[::-1]
                    elif event.key == pygame.K_RETURN:
                        if menu_color[0] == (100, 215, 0):
                            self.main_game()
                        elif menu_color[1] == (100, 215, 0):
                            print("Quit")
                            self.running = False
            self.clock.tick(60)

        pygame.quit()

if __name__ == "__main__":
    game = EGame()
    game.main_screen()

# def main() -> None:
#     bot = Bot(
#         verbose = True,
#         traced = True
#     )
#     bot.run()

# if __name__ == "__main__":
#     main()