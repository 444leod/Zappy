/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TileContent
*/

#pragma once

#include "Rocks.hpp"
#include "Egg.hpp"
#include "Character.hpp"

namespace gui {
    /**
     * @brief Class representing the content of a tile in the simulation
     * @note The tile can contain food, player, egg, rocks
    */
    class TileContent {
        public:
            /**
             * @brief Construct a new TileContent object
            */
            TileContent() = default;

            /**
             * @brief Destroy the TileContent object
            */
            ~TileContent() = default;

            /**
             * @brief Get the food of the tile
             * @return std::uint32_t The food of the tile
            */
            std::uint32_t food() const { return _food; }

            /**
             * @brief Set the food of the tile
             * @param food The food of the tile
            */
            void setFood(std::uint32_t food) { _food = food; }

            /**
             * @brief Get the player of the tile
             * @return Character The player of the tile
            */
            Character player() const { return _player; }

            /**
             * @brief Set the player of the tile
             * @param player The player of the tile
            */
            void setPlayer(Character player) { _player = player; }

            /**
             * @brief Get the egg of the tile
             * @return Egg The egg of the tile
            */
            Egg egg() const { return _egg; }

            /**
             * @brief Set the egg of the tile
             * @param egg The egg of the tile
            */
            void setEgg(Egg egg) { _egg = egg; }

            /**
             * @brief Get the rocks of the tile
             * @return Rocks The rocks of the tile
            */
            Rocks rocks() const { return _rocks; }

            /**
             * @brief Set the rocks of the tile
             * @param rocks The rocks of the tile
            */
            void setRocks(Rocks rocks) { _rocks = rocks; }

        private:
            std::uint32_t _food = 0;
            Character _player;
            Egg _egg;
            Rocks _rocks;
    };
}
