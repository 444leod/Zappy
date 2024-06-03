/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Character
*/

#pragma once

#include "Rocks.hpp"
#include "AEntities.hpp"
#include <map>
#include <vector>

namespace gui {
    /**
     * @brief Class representing the character in the simulation
     * @note The character is the player that can move on the map thanks to the IA
     * @note The character can move in 4 directions: NORTH, EAST, SOUTH, WEST
     * @note The character can have a food, a level, a position, an orientation and an inventory
    */
    class Character : public AEntities {
        public:
            /**
             * @brief default constructor of Character
            */
            Character() = default;

            /**
             * @brief Destroy the Character object
            */
            ~Character() = default;

            /**
             * @brief Get the food of the character
             * @return int The food of the character
            */
            int food() const { return _food; }

            /**
             * @brief Set the food of the character
             * @param food The food of the character
            */
            void setFood(int food) { _food = food; }

            /**
             * @brief Get the rocks of the character
             * @return Rocks The rocks of the character
            */
            Rocks rocks() const { return _rocks; }

            /**
             * @brief Set the rocks of the character
             * @param rocks The rocks of the character
            */
            void setRocks(Rocks rocks) { _rocks = rocks; }

            /**
             * @brief Get the player level
             * @return Vector2u The player level
            */
            std::uint32_t playerLevel() const { return _level; }

            /**
             * @brief Set the player level
             * @param playerLevel The player level
            */
            void setPlayerLevel(std::uint32_t playerLevel) { _level = playerLevel; }

        private:
            int _food = 0;
            std::uint32_t _level = 0;
            Rocks _rocks;
    };
}
