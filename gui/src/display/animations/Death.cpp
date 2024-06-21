/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Death
*/

#include "Death.hpp"

gui::animations::Death::Death(const std::string &skin, std::shared_ptr<gui::Player> player)
    : AAnimation(0, 0, "Death"), _skin(skin), _player(player)
{
    switch (_player->orientation()) {
        case gui::Orientation::SOUTH:
            break;
        case gui::Orientation::NORTH:
            break;
        case gui::Orientation::EAST:
            break;
        case gui::Orientation::WEST:
            break;
    }
    _player->setDisplayOffset({0, 0});
}

gui::animations::Death::~Death()
{
    _player->setDisplayOffset({0, 0});
}

void gui::animations::Death::update(float deltaTime)
{
    _passedTime += deltaTime;
    if (_passedTime >= 0.2) {
        _passedTime -= 0.2;
        _currentFrame++;
        if (_currentFrame >= _frameCount) {
            _currentFrame = 0;
        }
    }
}

void gui::animations::Death::draw(gui::ILibrary &lib)
{
    //To change (_skin got for the animation)
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(_skin), displayCoordinates.x(), displayCoordinates.y());
}
