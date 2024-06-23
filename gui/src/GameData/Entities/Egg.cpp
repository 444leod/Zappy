/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"

void gui::Egg::updateAnimation(UNUSED float deltaTime)
{
    _passedTime += deltaTime;
    if (_passedTime >= 0.1) {
        _passedTime -= 0.1;
        _currentFrame++;
        if (_currentFrame >= _frameCount) {
            _currentFrame = 0;
        }
    }
}

void gui::Egg::drawAnimation(UNUSED gui::ILibrary &lib)
{
    auto coords = _tileDisplayOffset + _displayOffset + _randomOffset;
    lib.display().draw(lib.textures().get("egg_eclosion_" + std::to_string(_currentFrame)), coords.x(), coords.y(), 0.5f);
    lib.display().print(("Egg " + std::to_string(_id)), lib.fonts().get("ClashRoyale"), coords.x(), coords.y(), gui::Color {100, 100, 100, 255}, 10);
}
