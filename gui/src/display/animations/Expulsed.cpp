/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Expulsed
*/

#include "Expulsed.hpp"

gui::animations::Expulsed::Expulsed(const std::string &skin, std::shared_ptr<gui::Player> player) : AAnimation(0, 0, "Expulsed")
{
    _skin = skin;
    _player = player;
    _direction = {0, 0};
}

gui::animations::Expulsed::~Expulsed()
{
}

void gui::animations::Expulsed::update(UNUSED float deltaTime)
{
}

void gui::animations::Expulsed::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
