/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Expulse
*/

#include "Expulse.hpp"

gui::animations::Expulse::Expulse(const std::string &skin, std::shared_ptr<gui::Player> player) : AAnimation(2.f, 0, "Expulse")
{
    _player = player;
    std::map<std::string, float> _frameBySkin = {
        {"bowler", 13},
        {"electro", 7},
        {"goblinBD", 5},
        {"goblin", 7},
        {"hog", 10},
        {"ice_wizard", 9},
        {"knight", 9}
    };
    if (_frameBySkin.find(skin) == _frameBySkin.end())
        throw std::invalid_argument("Invalid skin (Expulse)");
    _frameCount = _frameBySkin[skin];
    _skin = skin + "_eject_";
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
}

gui::animations::Expulse::~Expulse()
{
}

void gui::animations::Expulse::update(UNUSED float deltaTime)
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

void gui::animations::Expulse::draw(UNUSED gui::ILibrary &lib)
{
    const std::string& skin = _skin + std::to_string(_frameCount - _currentFrame - 1);
    auto displayCoordinates = _player->tileDisplayOffset() + _player->displayOffset();
    lib.display().draw(lib.textures().get(skin), displayCoordinates.x(), displayCoordinates.y(), 0.5f);
}
