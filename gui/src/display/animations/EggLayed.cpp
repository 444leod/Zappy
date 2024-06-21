/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** EggLayed
*/

#include "EggLayed.hpp"

gui::animations::EggLayed::EggLayed(const std::string &skin, std::shared_ptr<gui::Egg> egg) : AAnimation(0, 0, "EggLayed")
{
    _skin = skin;
    _egg = egg;
    _direction = {0, 0};
}

gui::animations::EggLayed::~EggLayed()
{
}

void gui::animations::EggLayed::update(UNUSED float deltaTime)
{
}

void gui::animations::EggLayed::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _egg->tileDisplayOffset() + _egg->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
