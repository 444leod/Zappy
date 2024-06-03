/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TileContent
*/

#pragma once

#include "Rocks.hpp"
#include "Egg.hpp"
#include "Character.hpp"

namespace gui {
    /**
     * @brief Class representing the content of a tile in the simulation
     * @note The tile can contain food, player, egg, rocks
    */
    class TileContent {
        public:
            /**
             * @brief Construct a new TileContent object
            */
            TileContent() = default;

            /**
             * @brief Destroy the TileContent object
            */
            ~TileContent() = default;

            /**
             * @brief Get the food of the tile
             * @return std::uint32_t The food of the tile
            */
            std::uint32_t food() const { return this->_food; }

            /**
             * @brief Set the food of the tile
             * @param food The food of the tile
            */
            void setFood(std::uint32_t food) { this->_food = food; }

            /**
             * @brief Get the entities of the tile
             * @return std::vector<AEntity&> The entities of the tile
            */
            std::vector<AEntity&> entity() const { return this->_entities; }

            /**
             * @brief Add an entity to the tile
             * @param entity The entity to add
            */
            void addEntity(AEntity& entity) { this->_entities.push_back(entity); }

            /**
             * @brief Remove an entity from the tile
             * @param id The id of the entity to remove
            */
            void removeEntity(std::uint32_t id) {
                for (auto it = this->_entities.begin(); it != this->_entities.end(); it++) {
                    if ((*it).entityId() == id) {
                        this->_entities.erase(it);
                        return;
                    }
                }
            }

            /**
             * @brief Get the rocks of the tile
             * @return Rocks The rocks of the tile
            */
            Rocks rocks() const { return this->_rocks; }

            /**
             * @brief Set the rocks of the tile
             * @param rocks The rocks of the tile
            */
            void setRocks(Rocks rocks) { this->_rocks = rocks; }

        private:
            std::uint32_t _food = 0;
            std::vector<AEntity&> _entities;
            Rocks _rocks;
    };
}
