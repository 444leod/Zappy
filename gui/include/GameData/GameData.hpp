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
#include <optional>
#include "Tiles/Tile.hpp"
#include "Entities/Player.hpp"
#include "Entities/Egg.hpp"
#include "Vector.hpp"
#include "Message.hpp"
#include "Tiles/Map.hpp"

#define UNUSED [[maybe_unused]]

namespace gui {
    /**
     * @brief Class representing the game data
     * @note The game data contains all the information about the game
     * @note The game data contains the map size, the tile content, the team names, the tile number, the player id, the message, the player position, the player level, the player inventory, the player
    */
    class GameData {
        public:
            static uint32_t frequency;
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
            void addTeamName(std::string teamName);

            /**
             * @brief Get the players vector
             * @return Player The player
            */
            std::vector<std::shared_ptr<Player>> players() const { return this->_players; }

            /**
             * @brief Add a player
             * @param player The player
            */
            void addPlayer(std::shared_ptr<Player> player);

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
             * @param egg The egg
            */
            void removeEgg(std::shared_ptr<Egg> egg);

            /**
             * @brief Get the messages
             * @return std::vector<message> The messages
            */
            std::vector<message_t> messages() const { return this->_messages; }

            /**
             * @brief Add a message
             * @param message The message
            */
            void addMessage(message_t message) { this->_messages.push_back(message); }

            /**
             * @brief Get the REFERENCE of the map
             * @return Map& The reference of the map
            */
            gui::Map& map() { return this->_map; }

            /**
             * @brief check if the given id corresponds to a player
             * @param playerId The player id
             * @return bool True if the player exists, false otherwise
            */
            bool playerExists(std::uint32_t playerId) const;

            /**
             * @brief check if the given team name exists
             * @param teamName The team name
             * @return bool True if the team exists, false otherwise
            */
            bool teamExists(const std::string &teamName) const;

            /**
             * @brief check if the given egg id exists
             * @param eggId The egg id
             * @return bool True if the egg exists, false otherwise
            */
            bool eggExists(std::uint32_t eggId) const;

            /**
             * @brief get the player by his id
             * @param playerId The player id
             * @return std::shared_ptr<Player> The player
            */
            std::optional<std::shared_ptr<Player>> getPlayerById(std::uint32_t playerId) const;

            /**
             * @brief get the egg by his id
             * @param eggId The egg id
             * @return std::shared_ptr<Egg> The egg
            */
            std::optional<std::shared_ptr<Egg>> getEggById(std::uint32_t eggId) const;

            /**
             * @brief display the command error parameters
            */
            void displayCommandParameter() const { std::cerr << "Command error: invalid parameters" << std::endl; }

            /**
             * @brief display the the server message
             * @param message The message
            */
            void displayServerMessage(const std::string &message) const { std::cerr << message << std::endl; }

            /**
             * @brief display unknown command
             * @param command The command
            */
            void displayUnknownCommand(const std::string &command) const { std::cerr << "Unknown command: " << command << std::endl; }

            /**
             * @brief set the team lose status
             * @param teamName The team name
            */
            void teamWin(std::string teamName);

            /**
             * @brief Get the time unit
             * @return std::uint32_t The time unit
            */
            std::uint32_t timeUnit() const { return this->_timeUnit; }

            /**
             * @brief Set the time unit
             * @param timeUnit The time unit
            */
            void setTimeUnit(std::uint32_t timeUnit) { this->_timeUnit = timeUnit; gui::GameData::frequency = timeUnit; }

            /**
             * @brief Set the game draw status
            */
            void teamDraw();

            std::pair<std::string, gui::Color> teamSkin(const std::string &teamName) const;

        private:
            std::vector<std::string> _teamNames = {};
            gui::Map _map;
            std::vector<std::shared_ptr<Player>> _players = {};
            std::vector<std::shared_ptr<Egg>> _eggs = {};
            std::vector<message_t> _messages = {};
            bool _teamLose = false;
            std::uint32_t _timeUnit = 0;
            bool _isDraw = false;
            std::map<std::string, std::pair<std::string, gui::Color>> _teamSkins = {};
            std::vector<gui::Color> _teamColors = {};
    };

    inline uint32_t GameData::frequency = 0;
}
