#!/usr/bin/env python3

import subprocess
import os
import ai_src.commands as cmd
from ai_src.data import TileContent, Collectibles
import unittest



class Inventory(unittest.TestCase):

    def test_basic_inv(self):
        res = cmd.Inventory().interpret_result("food 1, linemate 2, deraumere 3, sibur 4, mendiane 5, phiras 6, thystame 7")
        self.assertEqual(res, {
            "food": 1,
            "linemate": 2,
            "deraumere": 3,
            "sibur": 4,
            "mendiane": 5,
            "phiras": 6,
            "thystame": 7
        })
    
    def test_empty_inv(self):
        res = cmd.Inventory().interpret_result("food 0, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0")
        self.assertEqual(res, {
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        })
    
    def test_missing_elem_inv(self):
        res = cmd.Inventory().interpret_result("food 8, linemate 0, sibur 0, mendiane 0, phiras 5, thystame 0")
        self.assertEqual(res, {
            "food": 8,
            "linemate": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 5,
            "thystame": 0
        })

class Look(unittest.TestCase):

    def test_basic_look(self):
        res = cmd.Look().interpret_result("[player food, player, food food, mendiane]")
        self.assertEqual(res, {
            0: [TileContent(collectibles=Collectibles(food=1), nb_players=1)],
            1: [TileContent(nb_players=1), TileContent(collectibles=Collectibles(food=2)), TileContent(collectibles=Collectibles(mendiane=1))],
        })
    
    def test_empty_look(self):
        res = cmd.Look().interpret_result("[,,,]")
        self.assertEqual(res, {
            0: [TileContent()],
            1: [TileContent(), TileContent(), TileContent()],
        })

    def test_easy_padding_look(self):
        res = cmd.Look().interpret_result("[player food      ,    player    ,    food    food    , mendiane]")
        self.assertEqual(res, {
            0: [TileContent(collectibles=Collectibles(food=1), nb_players=1)],
            1: [TileContent(nb_players=1), TileContent(collectibles=Collectibles(food=2)), TileContent(collectibles=Collectibles(mendiane=1))],
        })
    def test_hard_padding_look(self):
        res = cmd.Look().interpret_result("   [   player              food        ,     player     ,food     food    , mendiane    ]    ")
        self.assertEqual(res, {
            0: [TileContent(collectibles=Collectibles(food=1), nb_players=1)],
            1: [TileContent(nb_players=1), TileContent(collectibles=Collectibles(food=2)), TileContent(collectibles=Collectibles(mendiane=1))],
        })
    
    def test_basic_level_two_look(self):
        res = cmd.Look().interpret_result("[player, , ,,,,,,food]")
        self.assertEqual(res, {
            0: [TileContent(nb_players=1)],
            1: [TileContent(), TileContent(), TileContent()],
            2: [TileContent(), TileContent(), TileContent(), TileContent(), TileContent(collectibles=Collectibles(food=1))],
        })

    def test_complex_level_two_look(self):
        res = cmd.Look().interpret_result("[player, , ,,,,,food food food linemate,food]")
        self.assertEqual(res, {
            0: [TileContent(nb_players=1)],
            1: [TileContent(), TileContent(), TileContent()],
            2: [TileContent(), TileContent(), TileContent(), TileContent(collectibles=Collectibles(food=3, linemate=1)), TileContent(collectibles=Collectibles(food=1))],
        })

    def test_level_three_look(self):
        res = cmd.Look().interpret_result("[player, , ,,,,,,food,,,,,,,linemate]")
        self.assertEqual(res, {
            0: [TileContent(nb_players=1)],
            1: [TileContent(), TileContent(), TileContent()],
            2: [TileContent(), TileContent(), TileContent(), TileContent(), TileContent(collectibles=Collectibles(food=1))],
            3: [TileContent(), TileContent(), TileContent(), TileContent(), TileContent(), TileContent(), TileContent(collectibles=Collectibles(linemate=1))],
        })

if __name__ == '__main__':
    unittest.main()