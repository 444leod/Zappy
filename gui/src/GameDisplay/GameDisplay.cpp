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

std::vector<std::uint32_t> generateRange(std::uint32_t start, std::uint32_t end)
{
    std::vector<std::uint32_t> range;

    for (std::uint32_t i = start; i < end; ++i)
        range.push_back(i);
    return range;
}


void gui::GameDisplay::drawMap(ILibrary& lib, GameData& data)
{
    auto mapSize = data.mapRef().mapSize();
    auto xRange = generateRange(0, mapSize.x());
    auto yRange = generateRange(0, mapSize.y());

    for (auto y : yRange) {
        for (auto x : xRange)
            this->drawMapTile(lib, x, y);
    }
}

void gui::GameDisplay::drawMapContent(ILibrary &lib, GameData& data)
{
    std::map<Vector2u, TileContent> mapContent = data.mapRef().mapContent();

    for (auto& [coordinates, tileContent] : mapContent) {
        this->drawRocks(lib, tileContent, coordinates);
        this->drawFood(lib, tileContent, coordinates);
    }
}

void gui::GameDisplay::drawMapTile(ILibrary& lib, std::uint32_t x, std::uint32_t y)
{
    lib.display().draw(lib.textures().get("map_tile"), x, y, 1);
}

void gui::GameDisplay::drawPlayers(ILibrary& lib, GameData& data)
{
    std::vector<std::shared_ptr<Character>> players = data.players();

    for (auto& player : players) {
        auto position = player->position();
        lib.display().draw(lib.textures().get("player"), position.x(), position.y(), 1);
    }
}

void gui::GameDisplay::drawEggs(ILibrary& lib, GameData& data)
{
    std::vector<std::shared_ptr<Egg>> eggs = data.eggs();

    for (auto& egg : eggs) {
        auto position = egg->position();
        lib.display().draw(lib.textures().get("egg"), position.x(), position.y(), 1);
    }
}

void gui::GameDisplay::drawRocks(ILibrary& lib, TileContent& tileContent, Vector2u coordinates)
{
    if (tileContent.rocks().linemate.quantity() > 0)
        lib.display().draw(lib.textures().get("linemate"), coordinates.x(), coordinates.y(), 1);
    if (tileContent.rocks().deraumere.quantity() > 0)
        lib.display().draw(lib.textures().get("deraumere"), coordinates.x(), coordinates.y(), 1);
    if (tileContent.rocks().sibur.quantity() > 0)
        lib.display().draw(lib.textures().get("sibur"), coordinates.x(), coordinates.y(), 1);
    if (tileContent.rocks().mendiane.quantity() > 0)
        lib.display().draw(lib.textures().get("mendiane"), coordinates.x(), coordinates.y(), 1);
    if (tileContent.rocks().phiras.quantity() > 0)
        lib.display().draw(lib.textures().get("phiras"), coordinates.x(), coordinates.y(), 1);
    if (tileContent.rocks().thystame.quantity() > 0)
        lib.display().draw(lib.textures().get("thystame"), coordinates.x(), coordinates.y(), 1);
}

void gui::GameDisplay::drawFood(ILibrary& lib, TileContent& tileContent, Vector2u coordinates)
{
    if (tileContent.food() > 0)
        lib.display().draw(lib.textures().get("food"), coordinates.x(), coordinates.y(), 1);
}

void gui::GameDisplay::drawMessages(ILibrary& lib, GameData& data)
{
    std::vector<Message> messages = data.messages();

    for (auto& message : messages) {
        lib.display().print(message.message, lib.fonts().get("font"), 0, 0);
    }
}

void gui::GameDisplay::drawTeamNames(ILibrary& lib, GameData& data)
{
    std::vector<std::string> teamNames = data.teamNames();

    for (auto& teamName : teamNames) {
        lib.display().print(teamName, lib.fonts().get("font"), 0, 0);
    }
}

void gui::GameDisplay::draw(ILibrary& lib, GameData& data)
{
    lib.display().clear(gui::Color{0, 0, 255, 0});
    this->drawMap(lib, data);
    this->drawMapContent(lib, data);
    this->drawEggs(lib, data);
    this->drawPlayers(lib, data);
    this->drawMessages(lib, data);
    this->drawTeamNames(lib, data);
}
