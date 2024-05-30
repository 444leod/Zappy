/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TileContent
*/

#ifndef TILECONTENT_HPP_
#define TILECONTENT_HPP_

#include "Rock.hpp"

/**
 * @brief Class representing the content of a tile in the simulation
 * @note The tile can contain food, player, egg, rock
*/
class TileContent {
    public:
        /**
         * @brief Construct a new TileContent object
        */
        TileContent() = default;

        /**
         * @brief Construct a new TileContent object
         * @param food The food of the tile
         * @param player The player of the tile
         * @param egg The egg of the tile
         * @param rock The rock of the tile
        */
        TileContent(int food, int player, int egg, Rock rock)
        {
            _food = food;
            _player = player;
            _egg = egg;
            _rock = rock;
        }

        /**
         * @brief Destroy the TileContent object
        */
        ~TileContent() = default;

        /**
         * @brief Get the food of the tile
         * @return int The food of the tile
        */
        int getFood() { return _food; }

        /**
         * @brief Set the food of the tile
         * @param food The food of the tile
        */
        void setFood(int food) { _food = food; }

        /**
         * @brief Get the player of the tile
         * @return int The player of the tile
        */
        int getPlayer() { return _player; }

        /**
         * @brief Set the player of the tile
         * @param player The player of the tile
        */
        void setPlayer(int player) { _player = player; }

        /**
         * @brief Get the egg of the tile
         * @return int The egg of the tile
        */
        int getEgg() { return _egg; }

        /**
         * @brief Set the egg of the tile
         * @param egg The egg of the tile
        */
        void setEgg(int egg) { _egg = egg; }

        /**
         * @brief Get the rock of the tile
         * @return Rock The rock of the tile
        */
        Rock getRock() { return _rock; }

        /**
         * @brief Set the rock of the tile
         * @param rock The rock of the tile
        */
        void setRock(Rock rock) { _rock = rock; }

    private:
        int _food = 0;
        int _player = 0;
        int _egg = 0;
        Rock _rock;
};

#endif /* !TILECONTENT_HPP_ */
