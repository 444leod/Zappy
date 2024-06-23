/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** idle
*/

#include "Idle.hpp"
#include "macros.hpp"
#include <iostream>

gui::animations::Idle::Idle(gui::Player& player)
    : AAnimation(0, 0, "idle"), _player(player)
{
}

gui::animations::Idle::~Idle()
{
}

void gui::animations::Idle::update(UNUSED float deltaTime)
{
}

void gui::animations::Idle::draw(gui::ILibrary &lib)
{
    auto coords = _player.tileDisplayOffset() + _player.displayOffset() + _player.randomOffset();
    auto skin = _player.skin();
    switch (_player.orientation()) {
        case gui::Orientation::SOUTH:
            skin += "_south";
            break;
        case gui::Orientation::NORTH:
            skin += "_north";
            break;
        case gui::Orientation::EAST:
            skin += "_east";
            break;
        case gui::Orientation::WEST:
            skin += "_west";
            break;
    }
    lib.display().draw(lib.textures().get(skin), coords.x(), coords.y(), 0.5f);
    lib.display().print(("Player " + std::to_string(_player.id())), lib.fonts().get("ClashRoyale"), coords.x(), coords.y(), _player.teamColor(), 10);
}

float gui::animations::Idle::remainingTime()
{
    return 1;
}

