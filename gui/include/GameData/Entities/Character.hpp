/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Character
*/

#pragma once

#include "Tiles/Rocks/Rocks.hpp"
#include "AEntity.hpp"

namespace gui {
    /**
     * @brief Class representing the character in the simulation
     * @note The character is the player that can move on the map thanks to the IA
     * @note The character can move in 4 directions: NORTH, EAST, SOUTH, WEST
     * @note The character can have a food, a level, a position, an orientation and rocks
    */
    class Character : public AEntity {
        public:
            /**
             * @brief default constructor of Character
            */
            Character() = default;

            /**
             * @brief Construct a new Character object for new player
             * @param id The id of the character
             * @param position The position of the character
             * @param orientation The orientation of the character
             * @param level The level of the character
             * @param teamName The team name of the character
            */
            Character(std::uint32_t id, Vector2u position, Orientation orientation, std::uint32_t level, std::string teamName)
                : AEntity(id, position, orientation, teamName), _level(level) {}

            /**
             * @brief Destroy the Character object
            */
            ~Character() = default;

            /**
             * @brief Get the food of the character
             * @return std::uint32_t The food of the character
            */
            std::uint32_t food() const { return this->_food; }

            /**
             * @brief Set the food of the character
             * @param food The food of the character
            */
            void setFood(std::uint32_t food) { this->_food = food; }

            /**
             * @brief Get the rocks of the character
             * @return Rocks The rocks of the character
            */
            Rocks rocks() const { return this->_rocks; }

            /**
             * @brief Set the rocks of the character
             * @param rocks The rocks of the character
            */
            void setRocks(Rocks rocks) { this->_rocks = rocks; }

            /**
             * @brief Get the player level
             * @return Vector2u The player level
            */
            std::uint32_t playerLevel() const { return this->_level; }

            /**
             * @brief Add 1 to the player level
            */
            void increasePlayerLevel() { this->_level += 1; }

            /**
             * @brief Set the player level
             * @param level The player level
            */
            void setPlayerLevel(std::uint32_t level) { this->_level = level; }

            /**
             * @brief Get the is laying an egg
             * @return bool The is laying an egg
            */
            bool layingAnEgg() const { return this->_isLayingAnEgg; }

            /**
             * @brief Set the is laying an egg
             * @param isLayingAnEgg The is laying an egg
            */
            void isLayingAnEgg(bool isLayingAnEgg) { this->_isLayingAnEgg = isLayingAnEgg; }

            /**
             * @brief Broadcast a message
             * @param message The message to broadcast
            */
            void broadcast(UNUSED message message) const { /* TO DO */};

            /**
             * @brief drop the ressource on the tile
            */
            void dropRessource() { this->_dropRessource = true; };

            /**
             * @brief set the player expulsed
             * @param isExpulsed The player expulsed
            */
            void expulsed(bool isExpulsed) { this->_isExpulsed = isExpulsed; }

            /**
             * @brief set the player picking ressource
             * @param pickingRessource The player picking ressource
            */
            void pickingRessource() { this->_pickingRessource = true; }

            /**
             * @brief set the player incantation
             * @param isincantation The player incantation
            */
            void incantation(bool isincantation) { this->_isincantation = isincantation; }

            /**
             * @brief set the player incantation result
             * @param position The position of the incantation
             * @param level The level of the incantation
             * @param result The result of the incantation
             * @note The result can be true or false
            */
            void incantationResult(UNUSED Vector2u position, UNUSED std::uint32_t level, bool result);

            /**
             * @brief set the player dead
             * @param isDead The player dead
            */
            void kill() { this->_isDead = true; }

        private:
            std::uint32_t _food = 0;
            std::uint32_t _level = 0;
            Rocks _rocks;
            bool _isLayingAnEgg = false;
            bool _dropRessource = false;
            bool _pickingRessource = false;
            bool _isExpulsed = false;
            bool _isincantation = false;
            bool _incantationResult = false;
            bool _isDead = false;
    };
}
