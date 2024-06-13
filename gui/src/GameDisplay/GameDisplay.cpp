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
    lib.display().setTileSize(64);
    lib.display().setWidth(1920);
    lib.display().setHeight(1080);

    // init textures
    // gui::TextureSpecification spec;
    // spec.graphical = gui::TextureImage{"assets/ground.png"};
    // lib.textures().load("ground", spec, 20, 10);
}

void gui::GameDisplay::onKeyPressed(ILibrary& lib, KeyCode key, bool shift)
{

}

void gui::GameDisplay::onMouseButtonPressed(ILibrary& lib, MouseButton button, int32_t x, int32_t y)
{

}

void gui::GameDisplay::draw(ILibrary& lib, GameData& data)
{
    lib.display().clear(gui::Color{0, 0, 255, 0});
    // drawMap(lib);
    // drawPlayers(lib);
    // drawEggs(lib);
    // drawResources(lib);
}
