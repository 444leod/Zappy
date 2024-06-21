/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IncantationStart
*/

#include "IncantationStart.hpp"

gui::animations::IncantationStart::IncantationStart(const std::string &skin, std::shared_ptr<gui::Player> player) : AAnimation(0, 0, "IncantationStart")
{
    _skin = skin;
    _player = player;
    _direction = {0, 0};
}

gui::animations::IncantationStart::~IncantationStart()
{
}

void gui::animations::IncantationStart::update(UNUSED float deltaTime)
{
}

void gui::animations::IncantationStart::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
