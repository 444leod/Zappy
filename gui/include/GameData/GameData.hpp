/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameData
*/

#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include "Tiles/TileContent.hpp"
#include "Entities/Character.hpp"
#include "Entities/Egg.hpp"
#include "Vector.hpp"
#include "Message.hpp"
#include "Tiles/Map.hpp"

namespace gui {
    /**
     * @brief Class representing the game data
     * @note The game data contains all the information about the game
     * @note The game data contains the map size, the tile content, the team names, the tile number, the player id, the message, the player position, the player level, the player inventory, the player
    */
    class GameData {
        public:
            /**
             * @brief Construct a new GameData object
            */
            GameData() = default;

            /**
             * @brief Destroy the GameData object
            */
            ~GameData() = default;

            /**
             * @brief Get the team names
             * @return std::vector<std::string> The team names
            */
            std::vector<std::string> teamNames() const { return this->_teamNames; }

            /**
             * @brief Add a team name
             * @param teamName The team name
            */
            void addTeamName(std::string teamName) { this->_teamNames.push_back(teamName); }

            /**
             * @brief Get the players vector
             * @return Character The player
            */
            std::vector<std::shared_ptr<Character>> players() const { return this->_players; }

            /**
             * @brief Add a player
             * @param player The player
            */
            void addPlayer(std::shared_ptr<Character> player);

            /**
             * @brief Remove a player
             * @param playerId The player id
            */
            void removePlayer(std::uint32_t playerId);

            /**
             * @brief Get the eggs
             * @return std::vector<Egg> The eggs
            */
            std::vector<std::shared_ptr<Egg>> eggs() const { return this->_eggs; }

            /**
             * @brief Add an egg
             * @param egg The egg
            */
            void addEgg(std::shared_ptr<Egg> egg);

            /**
             * @brief Remove an egg
             * @param eggId The egg id
            */
            void removeEgg(std::uint32_t eggId);

            /**
             * @brief Get the messages
             * @return std::vector<Message> The messages
            */
            std::vector<Message> messages() const { return this->_messages; }

            /**
             * @brief Add a message
             * @param message The message
            */
            void addMessage(Message message) { this->_messages.push_back(message); }

            /**
             * @brief Get the REFERENCE of the map
             * @return Map& The reference of the map
            */
            Map& mapRef() { return this->_map; }

            /**
             * @brief check if the given id corresponds to a player
             * @param playerId The player id
             * @return bool True if the player exists, false otherwise
            */
            bool playerExists(std::uint32_t playerId) const;

        private:
            std::vector<std::string> _teamNames = {};
            Map _map;
            std::vector<std::shared_ptr<Character>> _players = {};
            std::vector<std::shared_ptr<Egg>> _eggs = {};
            std::vector<Message> _messages = {};
    };
}
