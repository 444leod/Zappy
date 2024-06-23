/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Incantation
*/

#include "Incantation.hpp"
#include "SkinsConfig.hpp"
#include "GameData.hpp"


gui::animations::Incantation::Incantation(gui::Player& player) : AAnimation(300 / static_cast<float>(static_cast<float>(gui::GameData::frequency)), 0, "Incantation"), _player(player)
{
    auto skin = gui::skins::STRING_TO_SKIN[player.skin()];
    auto animations = gui::skins::ANIMATIONS_FRAMES[skin];
    for (auto &animation : animations) {
        if (animation.first == gui::skins::ANIMATIONS::INCANTATION) {
            _frameCount = animation.second;
            _skin = player.skin() + "_incantation";
            return;
        }
    }
    throw std::invalid_argument("Invalid skin (Incantation)");
}

gui::animations::Incantation::~Incantation()
{
}

void gui::animations::Incantation::update(UNUSED float deltaTime)
{
    _passedTime += deltaTime;
    if (_passedTime >= 0.1) {
        _passedTime -= 0.1;
        _duration -= 0.1;
        _currentFrame++;
        if (_currentFrame >= _frameCount) {
            _currentFrame = 0;
        }
    }
}

void gui::animations::Incantation::draw(UNUSED gui::ILibrary &lib)
{
    auto skin = _skin + "_" + std::to_string(_frameCount - _currentFrame - 1);
    auto displayCoordinates = _player.tileDisplayOffset() + _player.displayOffset();
    lib.display().draw(lib.textures().get(skin), displayCoordinates.x(), displayCoordinates.y());
}
