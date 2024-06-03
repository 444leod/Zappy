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
#include "TileContent.hpp"
#include "Entities/Character.hpp"
#include "Vector.hpp"
#include "Message.hpp"

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
             * @brief Get the player
             * @return Character The player
            */
            std::vector<Character> player() const { return this->_players; }

            /**
             * @brief Add a player
             * @param player The player
            */
            void addPlayer(Character player) { this->_players.push_back(player); }

            /**
             * @brief Remove a player
             * @param playerId The player id
            */
            void removePlayer(std::uint32_t playerId)
            {
                for (auto it = this->_players.begin(); it != this->_players.end(); it++) {
                    if (it->entityId() == playerId) {
                        this->_players.erase(it);
                        return;
                    }
                }
            }

            /**
             * @brief Get the eggs
             * @return std::vector<Egg> The eggs
            */
            std::vector<Egg> eggs() const { return this->_eggs; }

            /**
             * @brief Add an egg
             * @param egg The egg
            */
            void addEgg(Egg egg) { this->_eggs.push_back(egg); }

            /**
             * @brief Remove an egg
             * @param eggId The egg id
            */
            void removeEgg(std::uint32_t eggId)
            {
                for (auto it = this->_eggs.begin(); it != this->_eggs.end(); it++) {
                    if (it->entityId() == eggId) {
                        this->_eggs.erase(it);
                        return;
                    }
                }
            }

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

        private:
            std::vector<std::string> _teamNames = {};
            std::vector<Character> _players = {};
            std::vector<Egg> _eggs = {};
            std::vector<Message> _messages = {};
    };
}
