/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IncantationEnd
*/

#include "IncantationEnd.hpp"

gui::animations::IncantationEnd::IncantationEnd(const std::string &skin, std::shared_ptr<gui::Player> player) : AAnimation(0, 0, "IncantationEnd")
{
    _skin = skin;
    _player = player;
    _direction = {0, 0};
}

gui::animations::IncantationEnd::~IncantationEnd()
{
}

void gui::animations::IncantationEnd::update(UNUSED float deltaTime)
{
}

void gui::animations::IncantationEnd::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
