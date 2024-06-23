/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Player
*/

#include "Player.hpp"
#include "Idle.hpp"
#include "GameData.hpp"
#include "Death.hpp"

static std::map<std::string, uint32_t> _skinFrames = {
    {"bowler", 12},
    {"electro", 16},
    {"goblinBD", 16},
    {"goblin", 16},
    {"ice_wizard", 16},
    {"hog", 16},
    {"knight", 15}
};

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
        if (_skinFrames.find(_skin) == _skinFrames.end())
            throw std::runtime_error("Skin not found");
        _animations.push(std::make_shared<gui::animations::Idle>(*this));
    }
    auto animation = _animations.top();
    animation->update(deltaTime);
    if (animation->remainingTime() <= 0) {
        _animations.pop();
    }
}

void gui::Player::drawAnimation(gui::ILibrary &lib)
{
    auto offset = _displayOffset + _tileDisplayOffset;
    if (offset.x() < -200 || offset.y() < -200 || offset.x() > 1100 || offset.y() > 1300)
        return;
    if (_animations.size()) {
        _animations.top()->draw(lib);
    }
}

void gui::Player::kill(std::shared_ptr<gui::GameData> gameData)
{
    gameData->removePlayer(_id);
}

void gui::Player::incantate()
{
    _animations.push(std::make_shared<gui::animations::Incantation>(*this));
}
