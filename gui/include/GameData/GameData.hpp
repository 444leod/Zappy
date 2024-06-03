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
             * @brief Get the map size
             * @return Vector2u The map size
            */
            Vector2u mapSize() const { return _mapSize; }

            /**
             * @brief Set the map size
             * @param mapSize The map size
            */
            void setMapSize(Vector2u mapSize) { _mapSize = mapSize; }

            /**
             * @brief Get the tile content at specific coordinates
             * @param coordinates The coordinates of the tile
             * @return TileContent The tile content
             * @throw std::out_of_range If the coordinates are out of range
            */
            TileContent tileContent(Vector2u coordinates) const
            {
                auto it = _mapContent.find(coordinates);
                if (it != _mapContent.end())
                    return it->second;
                else
                    throw std::out_of_range("Coordinates out of range");
            }

            /**
             * @brief Check if the coordinates are valid
             * @param coordinates The coordinates
             * @return bool True if the coordinates are valid, false otherwise
            */
            bool isValidCoordinates(Vector2u coordinates) const
            {
                return (coordinates.x() < _mapSize.x() && coordinates.y() < _mapSize.y());
            }

            /**
             * @brief Set the tile content at specific coordinates
             * @param coordinates The coordinates of the tile
             * @param tileContent The new tile content
            */
            void setTileContent(Vector2u coordinates, TileContent tileContent)
            {
                if (!isValidCoordinates(coordinates))
                    throw std::out_of_range("Coordinates out of range");

                _mapContent[coordinates] = tileContent;
            }

            /**
             * @brief Get the map content
             * @return std::map<Vector2u, TileContent> The map content
            */
            std::map<Vector2u, TileContent> mapContent() const
            {
                return _mapContent;
            }

            /**
             * @brief Set the map content
             * @param mapContent The map content
            */
            void setMapContent(std::map<Vector2u, TileContent> mapContent)
            {
                for (auto &tile : mapContent) {
                    _mapContent[tile.first] = tile.second;
                }
            }

            /**
             * @brief Get the team names
             * @return std::vector<std::string> The team names
            */
            std::vector<std::string> teamNames() const { return _teamNames; }

            /**
             * @brief Add a team name
             * @param teamName The team name
            */
            void addTeamName(std::string teamName) { _teamNames.push_back(teamName); }

            /**
             * @brief Get the tile number
             * @return int The tile number
            */
            std::uint32_t tileNbr() const { return (_mapSize.x() * _mapSize.y()); }

            /**
             * @brief Get the player
             * @return Character The player
            */
            std::vector<Character> player() const { return _players; }

            /**
             * @brief Add a player
             * @param player The player
            */
            void addPlayer(Character player) { _players.push_back(player); }

            /**
             * @brief Remove a player
             * @param playerId The player id
            */
            void removePlayer(std::uint32_t playerId)
            {
                for (auto it = _players.begin(); it != _players.end(); it++) {
                    if (it->entityId() == playerId) {
                        _players.erase(it);
                        return;
                    }
                }
            }

        private:
            Vector2u _mapSize = {0, 0};
            std::map<Vector2u, TileContent> _mapContent = {};
            std::vector<std::string> _teamNames = {};
            std::vector<Character> _players = {};
            std::vector<Egg> _eggs = {};
            std::vector<Message> _message = {};
    };
}
