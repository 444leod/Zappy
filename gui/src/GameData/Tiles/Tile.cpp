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
        auto font = lib.fonts().get("ClashRoyale");
        lib.display().draw(lib.textures().get("grass"), this->_offset.x(), this->_offset.y(), 0.5f);
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t count = 0;

        auto drawItem = [&](const std::string& itemName, auto& item) {
            if (item.quantity()) {
                lib.display().print(std::to_string(item.quantity()), lib.fonts().get("ClashRoyale"), this->_offset.x() + x + 20, this->_offset.y() + y + 4, gui::Color{0, 0, 0, 255}, 10);
                lib.display().draw(lib.textures().get(itemName), this->_offset.x() + x, this->_offset.y() + y, 0.8f);
                count++;
                if (count % 3 == 0) {
                    y += 20;
                    x = 0;
                } else
                    x += 37;
            }
        };

        drawItem("linemate", _rocks.linemate);
        drawItem("deraumere", _rocks.deraumere);
        drawItem("sibur", _rocks.sibur);
        drawItem("mendiane", _rocks.mendiane);
        drawItem("phiras", _rocks.phiras);
        drawItem("thystame", _rocks.thystame);

        if (_food) {
            lib.display().print(std::to_string(_food), lib.fonts().get("ClashRoyale"), this->_offset.x() + x + 20, this->_offset.y() + y + 4, gui::Color{0, 0, 0, 255}, 10);
            lib.display().draw(lib.textures().get("food"), this->_offset.x() + x, this->_offset.y() + y, 0.8f);
        }
    }
}
