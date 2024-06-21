/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Incantation
*/

#include "Incantation.hpp"

gui::animations::Incantation::Incantation(const std::string &skin, std::shared_ptr<gui::Player> player) : AAnimation(0, 0, "Incantation")
{
    _skin = skin;
    _player = player;
    _direction = {0, 0};
}

gui::animations::Incantation::~Incantation()
{
}

void gui::animations::Incantation::update(UNUSED float deltaTime)
{
}

void gui::animations::Incantation::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
