/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AGameData
*/

#ifndef AGAMEDATA_HPP_
#define AGAMEDATA_HPP_

#include <vector>
#include <iostream>
#include <map>
#include "Tiles/TileContent.hpp"
#include "Character/Character.hpp"

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
         * @return std::pair<int, int> The map size
        */
        std::pair<int, int> getMapSize() { return _mapSize; }

        /**
         * @brief Set the map size
         * @param mapSize The map size
        */
        void setMapSize(std::pair<int, int> mapSize) { _mapSize = mapSize; }

        /**
         * @brief Get the tile content
         * @return std::map<std::pair<int, int>, TileContent> The tile content
        */
        std::map<std::pair<int, int>, TileContent> getTileContent() { return _tileContent; }

        /**
         * @brief Set the tile content
         * @param tileContent The tile content
        */
        void setTileContent(std::map<std::pair<int, int>, TileContent> tileContent) { _tileContent = tileContent; }

        /**
         * @brief Get the map content
         * @return std::map<std::pair<int, int>, TileContent> The map content
        */
        std::map<std::pair<int, int>, TileContent> getMapContent() { return _mapContent; }

        /**
         * @brief Set the map content
         * @param mapContent The map content
        */
        void setMapContent(std::map<std::pair<int, int>, TileContent> mapContent) { _mapContent = mapContent; }

        /**
         * @brief Get the team names
         * @return std::vector<std::string> The team names
        */
        std::vector<std::string> getTeamNames() { return _teamNames; }

        /**
         * @brief Set the team names
         * @param teamNames The team names
        */
        void setTeamNames(std::vector<std::string> teamNames) { _teamNames = teamNames; }

        /**
         * @brief Get the tile number
         * @return int The tile number
        */
        int getTileNbr() { return _tileNbr; }

        /**
         * @brief Set the tile number
         * @param tileNbr The tile number
        */
        void setTileNbr(int tileNbr) { _tileNbr = tileNbr; }

        /**
         * @brief Get the player id
         * @return int The player id
        */
        int getPlayerId() { return _playerId; }

        /**
         * @brief Set the player id
         * @param playerId The player id
        */
        void setPlayerId(int playerId) { _playerId = playerId; }

        /**
         * @brief Get the message
         * @return std::string The message
        */
        std::string getMessage() { return _message; }

        /**
         * @brief Set the message
         * @param message The message
        */
        void setMessage(std::string message) { _message = message; }

        /**
         * @brief Get the player position
         * @return std::map<int, Character> The player position
        */
        std::map<int, Character> getPlayerPosition() { return _playerPosition; }

        /**
         * @brief Set the player position
         * @param playerPosition The player position
        */
        void setPlayerPosition(std::map<int, Character> playerPosition) { _playerPosition = playerPosition; }

        /**
         * @brief Get the player level
         * @return std::map<int, Character> The player level
        */
        std::map<int, Character> getPlayerLevel() { return _playerLevel; }

        /**
         * @brief Set the player level
         * @param playerLevel The player level
        */
        void setPlayerLevel(std::map<int, Character> playerLevel) { _playerLevel = playerLevel; }

        /**
         * @brief Get the player inventory
         * @return std::map<int, Character> The player inventory
        */
        std::map<int, Character> getPlayerInventory() { return _playerInventory; }

        /**
         * @brief Set the player inventory
         * @param playerInventory The player inventory
        */
        void setPlayerInventory(std::map<int, Character> playerInventory) { _playerInventory = playerInventory; }

        /**
         * @brief Get the player
         * @return Character The player
        */
        Character getPlayer() { return _player; }

        /**
         * @brief Set the player
         * @param player The player
        */
        void setPlayer(Character player) { _player = player; }

    private:
        std::pair<int, int> _mapSize = {0, 0};
        std::map<std::pair<int, int>, TileContent> _tileContent = {};
        std::map<std::pair<int, int>, TileContent> _mapContent = {};
        std::vector<std::string> _teamNames = {};
        int _tileNbr = 0;
        int _playerId = 0;
        std::string _message = "";
        std::map<int, Character> _playerPosition = {};
        std::map<int, Character> _playerLevel = {};
        std::map<int, Character> _playerInventory = {};
        Character _player;
};

#endif /* !AGAMEDATA_HPP_ */
