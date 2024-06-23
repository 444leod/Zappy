/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#pragma once

#include "Tiles/Rocks/Rocks.hpp"
#include "AEntity.hpp"
#include "AAnimation.hpp"
#include "Incantation.hpp"

namespace gui {

    class GameData;

    /**
     * @brief Class representing the Player in the simulation
     * @note The Player is the player that can move on the map thanks to the IA
     * @note The Player can move in 4 directions: NORTH, EAST, SOUTH, WEST
     * @note The Player can have a food, a level, a position, an orientation and rocks
    */
    class Player : public AEntity {
        public:
            /**
             * @brief Construct a new Player object for new player
             * @param id The id of the Player
             * @param position The position of the Player
             * @param orientation The orientation of the Player
             * @param level The level of the Player
             * @param teamName The team name of the Player
            */
            Player(std::uint32_t id, Vector2u position, Orientation orientation, std::uint32_t level, std::string teamName)
                : AEntity(id, position, orientation, teamName), _level(level) {}

            /**
             * @brief Destroy the Player object
            */
            ~Player() = default;

            /**
             * @brief Get the food of the Player
             * @return std::uint32_t The food of the Player
            */
            std::uint32_t food() const { return this->_food; }

            /**
             * @brief Set the food of the Player
             * @param food The food of the Player
            */
            void setFood(std::uint32_t food) { this->_food = food; }

            /**
             * @brief Get the rocks of the Player
             * @return Rocks The rocks of the Player
            */
            Rocks rocks() const { return this->_rocks; }

            /**
             * @brief Set the rocks of the Player
             * @param rocks The rocks of the Player
            */
            void setRocks(Rocks rocks) { this->_rocks = rocks; }

            /**
             * @brief Add 1 to the player level
            */
            void increaseLevel() { this->_level += 1; }

            /**
             * @brief Set the player level
             * @param level The player level
            */
            void setLevel(std::uint32_t level) { this->_level = level; }

            /**
             * @brief Get the is laying an egg
             * @return bool The is laying an egg
            */
            bool layingAnEgg() const { return this->_isLayingAnEgg; }

            /**
             * @brief Set the is laying an egg
             * @param layEgg The is laying an egg
            */
            void layEgg(bool layEgg) { this->_isLayingAnEgg = layEgg; }

            /**
             * @brief Broadcast a message
             * @param message The message to broadcast
            */
            void broadcast(UNUSED message_t message) const { /* TO DO */};

            /**
             * @brief drop the ressource on the tile
            */
            void dropRessource() { this->_dropRessource = true; };

            /**
             * @brief set the player expulsed
             * @param isExpulsed The player expulsed
            */
            void expulse(bool isExpulsed) { this->_isExpulsed = isExpulsed; }

            /**
             * @brief set the player picking ressource
             * @param pickRessource The player picking ressource
            */
            void pickRessource() { this->_pickingRessource = true; }

            /**
             * @brief Make the player incantate
            */
            void incantate();

            /**
             * @brief set the player incantation result
             * @param position The position of the incantation
             * @param level The level of the incantation
             * @param result The result of the incantation
             * @note The result can be true or false
            */
            void updateEvolutionStatus(bool result);

            /**
             * @brief set the player dead
             * @param isDead The player dead
            */
            void kill(std::shared_ptr<gui::GameData> gameData);

            void updateAnimation(float deltaTime) override;
            void drawAnimation(ILibrary &lib) override;

            gui::AEntity::EntityType type() const { return gui::AEntity::EntityType::PLAYER; }

            std::uint32_t level() const { return this->_level; }

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
            gui::AEntity::EntityType _type = gui::AEntity::EntityType::PLAYER;
    };
}
