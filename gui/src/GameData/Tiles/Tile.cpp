/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#include "Tiles/Tile.hpp"

namespace gui {
    void Tile::removeEntity(std::uint32_t id)
    {
        for (auto it = this->_entities.begin(); it != this->_entities.end(); it++) {
            if ((*it)->id() == id) {
                this->_entities.erase(it);
                return;
            }
        }
        throw std::out_of_range("Entity not found");
    }

    void Tile::draw(gui::ILibrary& lib)
    {
        lib.display().draw(lib.textures().get("grass"), this->_offset.x(), this->_offset.y(), 0.5f);

        for (auto& entity : this->_entities) {
            entity->drawAnimation(lib);
        }
    }
}
