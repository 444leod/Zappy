/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** TileContent
*/

#include "Tiles/TileContent.hpp"

namespace gui {
    void TileContent::removeEntity(std::uint32_t id)
    {
        for (auto it = this->_entities.begin(); it != this->_entities.end(); it++) {
            if ((*it)->id() == id) {
                this->_entities.erase(it);
                return;
            }
        }
        throw std::out_of_range("Entity not found");
    }
}
