/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"

void gui::Egg::updateAnimation(UNUSED float deltaTime)
{
}

void gui::Egg::drawAnimation(UNUSED gui::ILibrary &lib)
{
    auto coords = _tileDisplayOffset + _displayOffset + _randomOffset;
    lib.display().draw(lib.textures().get("bowler_idle_" + std::to_string(0)), coords.x(), coords.y(), 0.5f);
    lib.display().print(("Egg " + std::to_string(_id)), lib.fonts().get("ClashRoyale"), coords.x(), coords.y(), gui::Color {100, 100, 100, 255}, 10);
}
