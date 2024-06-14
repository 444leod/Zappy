/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GameDisplay
*/

#pragma once

#include "GameDisplay.hpp"

void gui::GameDisplay::initialize(ILibrary& lib, GameData& data)
{
    lib.display().setTitle("Zappy GUI");
    lib.display().setFramerate(60);

    // init textures
}

void gui::GameDisplay::onKeyPressed(ILibrary& lib, KeyCode key, bool shift)
{

}

void gui::GameDisplay::onMouseButtonPressed(ILibrary& lib, MouseButton button, int32_t x, int32_t y)
{

}

void gui::GameDisplay::drawMap(ILibrary& lib, GameData& data)
{

}

void gui::GameDisplay::drawPlayers(ILibrary& lib, GameData& data)
{

}

void gui::GameDisplay::drawEggs(ILibrary& lib, GameData& data)
{

}

void gui::GameDisplay::drawMessages(ILibrary& lib, GameData& data)
{

}

void gui::GameDisplay::draw(ILibrary& lib, GameData& data)
{
    lib.display().clear(gui::Color{0, 0, 255, 0});
    drawMap(lib, data);
    drawPlayers(lib, data);
    drawEggs(lib, data);
    drawMessages(lib, data);
    drawTeamNames(lib, data);
}
