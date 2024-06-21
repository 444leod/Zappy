/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** EggLay
*/

#include "EggLay.hpp"

gui::animations::EggLay::EggLay(const std::string &skin, std::shared_ptr<gui::Egg> egg) : AAnimation(0, 0, "EggLay")
{
    _skin = skin;
    _egg = egg;
    _direction = {0, 0};
}

gui::animations::EggLay::~EggLay()
{
}

void gui::animations::EggLay::update(UNUSED float deltaTime)
{
}

void gui::animations::EggLay::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _egg->tileDisplayOffset() + _egg->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
