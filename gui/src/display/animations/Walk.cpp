/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Walk
*/

#include "Walk.hpp"

gui::animations::Walk::Walk(const std::string &skin, std::shared_ptr<gui::Player> player)
    : AAnimation(4.5f, 13, "walk"), _skin(skin), _player(player)
{
    _skin += "_walk_";
    switch (_player->orientation()) {
        case gui::Orientation::SOUTH:
            _skin += "south_";
            _direction = {0, 1};
            break;
        case gui::Orientation::NORTH:
            _skin += "north_";
            _direction = {0, -1};
            break;
        case gui::Orientation::EAST:
            _skin += "east_";
            _direction = {1, 0};
            break;
        case gui::Orientation::WEST:
            _skin += "west_";
            _direction = {-1, 0};
            break;
    }
    _player->setDisplayOffset(_player->displayOffset() - (_direction * 120));
}

gui::animations::Walk::~Walk()
{
    _player->setDisplayOffset({0, 0});
}

void gui::animations::Walk::update(float deltaTime)
{
    _passedTime += deltaTime;
    if (_passedTime >= 0.2) {
        _passedTime -= 0.2;
        _duration -= 0.2;
        _player->setDisplayOffset(_player->displayOffset() + (_direction * 4));
        _currentFrame++;
        if (_currentFrame >= _frameCount) {
            _currentFrame = 0;
        }

    }
}

void gui::animations::Walk::draw(gui::ILibrary &lib)
{
    const std::string& skin = _skin + std::to_string(_currentFrame);
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(skin), displayCoordinates.x(), displayCoordinates.y(), 0.5f);
}
