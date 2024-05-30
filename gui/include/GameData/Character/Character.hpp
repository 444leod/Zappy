/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "Rock.hpp"

/**
 * @brief Class representing the character in the simulation
 * @note The character is the player that can move on the map thanks to the IA
 * @note The character can move in 4 directions: NORTH, EAST, SOUTH, WEST
 * @note The character can have a food, a level, a position, an orientation and an inventory
*/
class Character {
    public:
        /**
         * @brief Enum for the orientation of the character
         * @note NORTH = 1
         * @note EAST = 2
         * @note SOUTH = 3
         * @note WEST = 4
        */
        enum Orientation {
            NORTH = 1,
            EAST,
            SOUTH,
            WEST
        };

        struct vec2i {
            int x;
            int y;
        };

        /**
         * @brief Construct a new Character object
         * @param food The food of the character
         * @param player The player of the character
         * @param egg The egg of the character
         * @param level The level of the character
         * @param x The x position of the character
         * @param y The y position of the character
         * @param orientation The orientation of the character
         * @param rock The rock of the character
         * @note The default orientation is NORTH
         * @note The default values are 0
        */
        Character(int food, int player, int egg, int level, int x, int y, Orientation orientation, Rock rock)
        {
            _food = food;
            _level = level;
            _position.x = x;
            _position.y = y;
            _orientation = orientation;
            _rock = rock;
        }

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
        int getFood() { return _food; }

        /**
         * @brief Set the food of the character
         * @param food The food of the character
        */
        void setFood(int food) { _food = food; }

        /**
         * @brief Get the level of the character
         * @return int The level of the character
        */
        int getLevel() { return _level; }

        /**
         * @brief Set the level of the character
         * @param level The level of the character
        */
        void setLevel(int level) { _level = level; }

        /**
         * @brief Get the x position of the character
         * @return int The x position of the character
        */
        int getX() { return _position.x; }

        /**
         * @brief Set the x position of the character
         * @param x The x position of the character
        */
        void setX(int x) { _position.x = x; }

        /**
         * @brief Get the y position of the character
         * @return int The y position of the character
        */
        int getY() { return _position.y; }

        /**
         * @brief Set the y position of the character
         * @param y The y position of the character
        */
        void setY(int y) { _position.y = y; }

        /**
         * @brief Get the orientation of the character
         * @return Orientation The orientation of the character
        */
        Orientation getOrientation() { return _orientation; }

        /**
         * @brief Set the orientation of the character
         * @param orientation The orientation of the character
        */
        void setOrientation(Orientation orientation) { _orientation = orientation; }

        /**
         * @brief Get the rock of the character
         * @return Rock The rock of the character
        */
        Rock getRock() { return _rock; }

        /**
         * @brief Set the rock of the character
         * @param rock The rock of the character
        */
        void setRock(Rock rock) { _rock = rock; }

    private:
        int _food = 0;
        int _level = 0;
        vec2i _position = {0, 0};
        Orientation _orientation = NORTH;
        Rock _rock;
};

#endif /* !CHARACTER_HPP_ */
