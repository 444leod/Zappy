/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#pragma once

#include <map>
#include <memory>
#include <queue>
#include "Tile.hpp"
#include "Vector.hpp"

namespace gui {
    /**
     * @brief Class representing the map in the simulation
     * @note The map contains the tiles
    */
    class Map {
        public:
            /**
             * @brief Construct a new Map object
            */
            Map() = default;

            /**
             * @brief Destroy the Map object
            */
            ~Map() = default;

            /**
             * @brief Get the tile number
             * @return int The tile number
            */
            std::uint32_t tileNbr() const { return (this->_size.x() * this->_size.y()); }

            /**
             * @brief Get the map size
             * @return Vector2u The map size
            */
            Vector2u size() const { return this->_size; }

            /**
             * @brief Get the tile at specific coordinates
             * @param coordinates The coordinates of the tile
             * @return Tile The tile
             * @throw std::out_of_range If the coordinates are out of range
            */
            std::shared_ptr<Tile> at(Vector2u coordinates) const;

            /**
             * @brief Check if the coordinates are valid
             * @param coordinates The coordinates
             * @return bool True if the coordinates are valid, false otherwise
            */
            bool isValidCoordinates(Vector2u coordinates) const { return (coordinates.x() < this->_size.x() && coordinates.y() < this->_size.y()); }

            /**
             * @brief Init the map content
             * @param size The map size
             * @param gameData The game data
            */
            void initializeMap(Vector2u size);

            /**
             * @brief Queue a player connexion if the map is not initialized
             * @param fullCommand The full command
            */
            void queuePlayerConnexion(std::string fullCommand);

            /**
             * @brief Get the player connexion queue
             * @return std::queue<std::string> The player connexion queue
            */
            std::queue<std::string> playerConnexionQueue() const { return this->_playerConnexionQueue; }

        private:
            Vector2u _size = {0, 0};
            std::map<Vector2u, std::shared_ptr<Tile>> _mapContent = {};
            std::queue<std::string> _playerConnexionQueue = {};
    };
}
