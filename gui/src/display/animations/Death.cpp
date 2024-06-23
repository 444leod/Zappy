/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Death
*/

#include "Death.hpp"

gui::animations::Death::Death(gui::Player& player, std::shared_ptr<gui::GameData> gameData)
    : AAnimation(0.5f, 0, "death"),_player(player), _gameData(gameData)
{
}

gui::animations::Death::~Death()
{
    _player.setDisplayOffset({0, 0});
    _gameData->removePlayer(_player.id());
}

void gui::animations::Death::update(float deltaTime)
{
    _passedTime += deltaTime;
    if (_passedTime >= 0.1) {
        _passedTime -= 0.1;
        _duration -= 0.1;
        _scale *= 0.9;
    }
}

void gui::animations::Death::draw(gui::ILibrary &lib)
{
    auto displayCoordinates = _player.tileDisplayOffset() + _player.displayOffset();

    lib.display().draw(lib.textures().get(_player.skin()), displayCoordinates.x(), displayCoordinates.y());
}
