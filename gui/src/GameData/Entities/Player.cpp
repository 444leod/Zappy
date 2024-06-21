/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "Player.hpp"
#include "Idle.hpp"

void gui::Player::updateEvolutionStatus(bool result)
{
    if (result)
        _incantationResult = true;
    else
        _incantationResult = false;
}

void gui::Player::updateAnimation(float deltaTime)
{
    if (!_animations.size()) {
        this->pushAnimation(std::make_shared<gui::animations::Idle>(this->_skin, *this));
    }
    auto animation = _animations.top();
    animation->update(deltaTime);
    if (animation->remainingTime() <= 0) {
        _animations.pop();
    }
}

void gui::Player::drawAnimation(gui::ILibrary &lib)
{
    if (_animations.size()) {
        _animations.top()->draw(lib);
    }
}
