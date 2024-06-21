/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#pragma once

#include "Tiles/Rocks/Rocks.hpp"
#include "Entities/Egg.hpp"
#include "Entities/Player.hpp"
#include "ILibrary.hpp"

namespace gui {
    /**
     * @brief Class representing the content of a tile in the simulation
     * @note The tile can contain food, player, egg, rocks
    */
    class Tile {
        public:
            /**
             * @brief Construct a new Tile object
            */
            Tile() = default;

            /**
             * @brief Destroy the Tile object
            */
            ~Tile() = default;

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
             * @return std::vector<std::shared_ptr<AEntity>> The entities of the tile
            */
            std::vector<std::shared_ptr<AEntity>> entities() const { return this->_entities; }

            /**
             * @brief Add an entity to the tile
             * @param entity The entity to add
            */
            void addEntity(std::shared_ptr<AEntity> entity) {
                entity->setTileDisplayOffset(this->_offset);
                this->_entities.push_back(entity);
            }

            /**
             * @brief Remove an entity from the tile
             * @param id The id of the entity to remove
            */
            void removeEntity(std::uint32_t id);

            /**
             * @brief Get the access to the rocks of the tile
             * @return Rocks The rocks of the tile
            */
            Rocks &rocks() { return this->_rocks; }

            void draw(gui::ILibrary& lib);

            Vector2f offset() { return this->_offset; }

            void setOffset(Vector2f offset) { this->_offset = offset; }

        private:
            std::uint32_t _food = 0;
            std::vector<std::shared_ptr<AEntity>> _entities;
            Rocks _rocks;
            Vector2f _offset = {0, 0};
    };
}
