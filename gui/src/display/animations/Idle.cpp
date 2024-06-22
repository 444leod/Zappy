/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** idle
*/

#include "Idle.hpp"
#include "macros.hpp"
#include <iostream>

gui::animations::Idle::Idle(const std::string &skin, gui::Player& player, float duration, uint32_t frameCount)
    : AAnimation(duration, frameCount, "idle"), _skin(skin), _player(player)
{
}

gui::animations::Idle::~Idle()
{
}

void gui::animations::Idle::update(UNUSED float deltaTime)
{
    _passedTime += deltaTime;
    if (_passedTime >= 0.1) {
        _passedTime -= 0.1;
        _duration -= 0.1;
        _currentFrame++;
        if (_currentFrame == _frameCount) {
            _currentFrame = 0;
        }
    }
}

void gui::animations::Idle::draw(UNUSED gui::ILibrary &lib)
{
    auto coords = _player.tileDisplayOffset() + _player.displayOffset() + _player.randomOffset();
    lib.display().draw(lib.textures().get(_player.skin() + "_idle_" + std::to_string(_currentFrame)), coords.x(), coords.y(), 0.5f);
    lib.display().print(("Player " + std::to_string(_player.id())), lib.fonts().get("ClashRoyale"), coords.x(), coords.y(), _player.teamColor(), 10);
}

float gui::animations::Idle::remainingTime()
{
    return 1;
}
