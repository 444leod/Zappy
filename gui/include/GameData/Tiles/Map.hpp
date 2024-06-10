/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#pragma once

#include <map>
#include "TileContent.hpp"
#include "Vector.hpp"

namespace gui {
    /**
     * @brief Class representing the map in the simulation
     * @note Map is a resource that can be found on the map
     * @note Herited from TileContent class
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
            std::uint32_t tileNbr() const { return (this->_mapSize.x() * this->_mapSize.y()); }

            /**
             * @brief Get the map size
             * @return Vector2u The map size
            */
            Vector2u mapSize() const { return this->_mapSize; }

            /**
             * @brief Set the map size
             * @param mapSize The map size
            */
            void setMapSize(Vector2u mapSize) { this->_mapSize = mapSize; }

            /**
             * @brief Get the tile content at specific coordinates
             * @param coordinates The coordinates of the tile
             * @return TileContent The tile content
             * @throw std::out_of_range If the coordinates are out of range
            */
            TileContent getTileContentByCoordinates(Vector2u coordinates) const;

            /**
             * @brief Check if the coordinates are valid
             * @param coordinates The coordinates
             * @return bool True if the coordinates are valid, false otherwise
            */
            bool isValidCoordinates(Vector2u coordinates) const { return (coordinates.x() < this->_mapSize.x() && coordinates.y() < this->_mapSize.y()); }

            /**
             * @brief Set the tile content at specific coordinates
             * @param coordinates The coordinates of the tile
             * @param tileContent The new tile content
             * @throw std::out_of_range If the coordinates are out of range
            */
            void setTileContentByCoordinates(Vector2u coordinates, TileContent tileContent);

            /**
             * @brief Get the map content
             * @return std::map<Vector2u, TileContent> The map content
            */
            std::map<Vector2u, TileContent> mapContent() const { return this->_mapContent; }

            /**
             * @brief Set the map content
             * @param mapContent The map content
            */
            void setMapContent(std::map<Vector2u, TileContent> mapContent);

            /**
             * @brief Remove an entity from a tile
             * @param coordinates The coordinates of the tile
             * @param id The id of the entity to remove
            */
            void removeEntityAtCoordinates(Vector2u coordinates, std::uint32_t id) { this->_mapContent[coordinates].removeEntity(id); }

        private:
            Vector2u _mapSize = {0, 0};
            std::map<Vector2u, TileContent> _mapContent = {};
    };
}
