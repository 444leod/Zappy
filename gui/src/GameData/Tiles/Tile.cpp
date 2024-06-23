/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#include "Tiles/Tile.hpp"

namespace gui {
    void Tile::removeEntity(std::uint32_t entityId)
    {
        for (auto it = this->_entities.begin(); it != this->_entities.end(); it++) {
            if ((*it)->entityId() == entityId) {
                this->_entities.erase(it);
                return;
            }
        }
        throw std::out_of_range("Entity not found");
    }

    void Tile::removeEntity(std::shared_ptr<AEntity> entity)
    {

        for (auto it = this->_entities.begin(); it != this->_entities.end(); it++) {
            if ((*it)->entityId() == entity->entityId()) {
                this->_entities.erase(it);
                return;
            }
        }
        throw std::out_of_range("Entity not found");
    }

    void Tile::draw(gui::ILibrary& lib)
    {
        if (_offset.x() < -200 || _offset.y() < -200 || _offset.x() > 1100 || _offset.y() > 1100)
            return;
        auto font = lib.fonts().get("ClashRoyale");
        lib.display().draw(lib.textures().get("grass"), this->_offset.x(), this->_offset.y(), 0.5f);
        uint32_t y = 0;
        if (_rocks.linemate.quantity()) {
            lib.display().print("li: " + std::to_string(_rocks.linemate.quantity()), font, this->_offset.x(), this->_offset.y() + y, gui::Color{255, 50, 0, 50}, 10);
            y += 15;
        }
        if (_rocks.deraumere.quantity()) {
            lib.display().print("de: " + std::to_string(_rocks.deraumere.quantity()), font, this->_offset.x(), this->_offset.y() + y, gui::Color(0, 50, 0, 255), 10);
            y += 15;
        }
        if (_rocks.sibur.quantity()) {
            lib.display().print("si: " + std::to_string(_rocks.sibur.quantity()), font, this->_offset.x(), this->_offset.y() + y, gui::Color(0, 0, 50, 255), 10);
            y += 15;
        }
        if (_rocks.mendiane.quantity()) {
            lib.display().print("me: " + std::to_string(_rocks.mendiane.quantity()), font, this->_offset.x(), this->_offset.y() + y, gui::Color(50, 50, 0, 255), 10);
            y += 15;
        }
        if (_rocks.phiras.quantity()) {
            lib.display().print("ph: " + std::to_string(_rocks.phiras.quantity()), font, this->_offset.x(), this->_offset.y() + y, gui::Color(0, 50, 50, 255), 10);
            y += 15;
        }
        if (_rocks.thystame.quantity()) {
            lib.display().print("th: " + std::to_string(_rocks.thystame.quantity()), font, this->_offset.x(), this->_offset.y() + y, gui::Color(50, 0, 50, 255), 10);
            y += 15;
        }
        if (_food) {
            lib.display().print("food: " + std::to_string(_food), font, this->_offset.x(), this->_offset.y() + y, gui::Color(200, 200, 200, 255), 10);
            y += 15;
        }
    }

    void Tile::setOffset(Vector2f offset)
    {
        _offset = offset;
        for (auto& entity : _entities) {
            entity->setTileDisplayOffset(_offset);
        }
    }
}
