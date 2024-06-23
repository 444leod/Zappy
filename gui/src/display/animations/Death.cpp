/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Death
*/

#include "Death.hpp"

gui::animations::Death::Death(gui::Player& player, std::shared_ptr<gui::GameData> gameData)
    : AAnimation(0.5f, 0, "death") ,_player(player), _gameData(gameData)
{
    _scale = 0.5f;
    _skin = player.skin();
    switch (_player.orientation()) {
        case gui::Orientation::SOUTH:
            _skin += "_south";
            break;
        case gui::Orientation::NORTH:
            _skin += "_north";
            break;
        case gui::Orientation::EAST:
            _skin += "_east";
            break;
        case gui::Orientation::WEST:
            _skin += "_west";
            break;
    }
    _pos = _player.tileDisplayOffset() + _player.displayOffset();
}

gui::animations::Death::~Death()
{
    _player.setDisplayOffset({0, 0});
    _gameData->removePlayer(_player.id());
}

void gui::animations::Death::update(float deltaTime)
{
    _passedTime += deltaTime;
    while (_passedTime >= 0.01) {
        _passedTime -= 0.01;
        _duration -= 0.01;
        _scale *= 0.9;
        _frameCount++;
    }
}

void gui::animations::Death::draw(gui::ILibrary &lib)
{
    lib.display().draw(lib.textures().get(_skin), _pos.x() + _frameCount, _pos.y() + _frameCount, _scale);
}
