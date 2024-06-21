/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Expulse
*/

#include "Expulse.hpp"

gui::animations::Expulse::Expulse(const std::string &skin, std::shared_ptr<gui::Player> player) : AAnimation(0, 0, "Expulse")
{
    _skin = skin;
    _player = player;
    _direction = {0, 0};
}

gui::animations::Expulse::~Expulse()
{
}

void gui::animations::Expulse::update(UNUSED float deltaTime)
{
}

void gui::animations::Expulse::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
