/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GameDisplay
*/

#include "GameDisplay.hpp"
#include "GameConstants.hpp"
#include "GameData/Tiles/TileContent.hpp"

void gui::GameDisplay::initialize(ILibrary& lib)
{
    lib.display().setTitle("Zappy GUI");
    lib.display().setFramerate(60);
    lib.display().setWidth(1920);
    lib.display().setHeight(1080);

    // Textures
//    gui::TextureSpecification spec;
//    spec.graphical = gui::TextureImage{MAP_TILE_PATH};
//    lib.textures().load("map_tile", spec);
//    spec.graphical = gui::TextureImage{PLAYER_PATH};
//    lib.textures().load("player", spec);
//    spec.graphical = gui::TextureImage{EGG_PATH};
//    lib.textures().load("egg", spec);
//    spec.graphical = gui::TextureImage{FOOD_PATH};
//    lib.textures().load("food", spec);
//    spec.graphical = gui::TextureImage{LINEMATE_PATH};
//    lib.textures().load("linemate", spec);
//    spec.graphical = gui::TextureImage{DERAUMERE_PATH};
//    lib.textures().load("deraumere", spec);
//    spec.graphical = gui::TextureImage{SIBUR_PATH};
//    lib.textures().load("sibur", spec);
//    spec.graphical = gui::TextureImage{MENDIANE_PATH};
//    lib.textures().load("mendiane", spec);
//    spec.graphical = gui::TextureImage{PHIRAS_PATH};
//    lib.textures().load("phiras", spec);
//    spec.graphical = gui::TextureImage{THYSTAME_PATH};
//    lib.textures().load("thystame", spec);

    // Fonts
//    gui::FontSpecification text {
//            .color = gui::Color {200, 200, 200, 255},
//            .size = 32,
//            .path = FONT_PATH
//        };
//    lib.fonts().load("font", text);
}

void gui::GameDisplay::draw(ILibrary& lib, [[maybe_unused]]GameData& data)
{
    lib.display().clear(gui::Color{0, 0, 255, 0});
    lib.display().flush();
}
