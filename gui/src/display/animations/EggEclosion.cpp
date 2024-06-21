/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** EggEclosion
*/

#include "EggEclosion.hpp"

gui::animations::EggEclosion::EggEclosion(const std::string &skin, std::shared_ptr<gui::Egg> egg) : AAnimation(0, 0, "EggEclosion")
{
    _skin = skin;
    _egg = egg;
    _direction = {0, 0};
}

gui::animations::EggEclosion::~EggEclosion()
{
}

void gui::animations::EggEclosion::update(UNUSED float deltaTime)
{
}

void gui::animations::EggEclosion::draw(UNUSED gui::ILibrary &lib)
{
    auto displayCoordinates = _egg->tileDisplayOffset() + _egg->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
