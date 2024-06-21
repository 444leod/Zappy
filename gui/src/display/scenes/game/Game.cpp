/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/

#include "Game.hpp"
#include "Ppo.hpp"
#include "Mct.hpp"

void gui::scenes::Game::initialize(UNUSED gui::ILibrary& lib)
{
    gui::TextureSpecification spec;
    spec.graphical.path = "gui/assets/bowlerSpriteSheet.png";
    spec.graphical.subrect = {0, 0, 122, 132};

    std::map<std::string, std::vector<std::pair<std::string, uint8_t>>> _frames = {
        {"bowlerSpriteSheet.png", {
            {"bowler_eject_south_", 13},
            {"bowler_eject_west_", 13},
            {"bowler_eject_east_", 13},
            {"bowler_eject_north_", 13},
            {"bowler_walk_south_", 13},
            {"bowler_walk_west_", 13},
            {"bowler_walk_east_", 13},
            {"bowler_walk_north_", 13},
            {"bowler_idle_", 12}
        }},
        {"electroSpriteSheet.png", {
            {"electro_eject_south_", 7},
            {"electro_eject_west_", 7},
            {"electro_eject_east_", 7},
            {"electro_eject_north_", 7},
            {"electro_walk_south_", 8},
            {"electro_walk_west_", 8},
            {"electro_walk_east_", 8},
            {"electro_walk_north_", 8},
            {"electro_idle_", 16}
        }},
        {"goblinBDSpriteSheet.png", {
            {"goblinBD_eject_south_", 5},
            {"goblinBD_eject_west_", 5},
            {"goblinBD_eject_east_", 5},
            {"goblinBD_eject_north_", 5},
            {"goblinBD_walk_south_", 8},
            {"goblinBD_walk_west_", 8},
            {"goblinBD_walk_east_", 8},
            {"goblinBD_walk_north_", 8},
            {"goblinBD_idle_", 16}
        }},
        {"goblinSpriteSheet.png", {
            {"goblin_eject_south_", 7},
            {"goblin_eject_west_", 7},
            {"goblin_eject_east_", 7},
            {"goblin_eject_north_", 7},
            {"goblin_walk_south_", 8},
            {"goblin_walk_west_", 8},
            {"goblin_walk_east_", 8},
            {"goblin_walk_north_", 8},
            {"goblin_idle_", 16}
        }},
        {"hogSpriteSheet.png", {
            {"hog_eject_south_", 10},
            {"hog_eject_west_", 10},
            {"hog_eject_east_", 10},
            {"hog_eject_north_", 10},
            {"hog_walk_south_", 8},
            {"hog_walk_west_", 8},
            {"hog_walk_east_", 8},
            {"hog_walk_north_", 8},
            {"hog_idle_", 16}
        }},
        {"iceWizardSpriteSheet.png", {
            {"ice_wizard_eject_south_", 9},
            {"ice_wizard_eject_west_", 9},
            {"ice_wizard_eject_east_", 9},
            {"ice_wizard_eject_north_", 9},
            {"ice_wizard_walk_south_", 8},
            {"ice_wizard_walk_west_", 8},
            {"ice_wizard_walk_east_", 8},
            {"ice_wizard_walk_north_", 8},
            {"ice_wizard_idle_", 16}
        }}
    };

    uint32_t frameIndex = 0;
    for (auto& [skin, frames] : _frames) {
        spec.graphical.path = "gui/assets/" + skin;
        for (auto& [frame, count] : frames) {
            for (uint8_t i = 0; i < count; i++) {
                spec.graphical.subrect->x = i * 122;
                spec.graphical.subrect->y = frameIndex * 132;
                lib.textures().load(frame + std::to_string(i), spec);
            }
            frameIndex++;
        }
        frameIndex = 0;
    }

    spec.graphical.path = "gui/assets/map_sprite_sheet.png";
    spec.graphical.subrect = {8071, 2014, 220, 220};
    lib.textures().load("grass", spec);

    spec.graphical.path = "gui/assets/eggs_sprite_sheet.png";
    spec.graphical.subrect = {0, 580, 630, 572};
    lib.textures().load("egg", spec);

}

void gui::scenes::Game::onKeyPressed(UNUSED gui::ILibrary& lib, UNUSED gui::KeyCode key, UNUSED bool shift)
{
}

void gui::scenes::Game::onMouseButtonPressed(UNUSED gui::ILibrary& lib, UNUSED gui::MouseButton button, UNUSED int32_t x, UNUSED int32_t y)
{
}

void gui::scenes::Game::update(UNUSED gui::ILibrary& lib, UNUSED float deltaTime)
{
    static float passedTime = 0;
    passedTime += deltaTime;

    if (passedTime >= _tickTime) {
        _passedTicks++;
        passedTime -= _tickTime;
        //do all other requests
        for (auto& player : _gameData->players()) {
            Ppo().stage(_serverCli, std::to_string(player->id()));
        }

        if (_passedTicks != 0 && _passedTicks % 10 == 0) {
            std::cout << "MCT\n";
            Mct().stage(_serverCli);
        }
    }

    for (auto& player : _gameData->players()) {
        player->updateAnimation(deltaTime);
    }
    for (auto& egg : _gameData->eggs()) {
        egg->updateAnimation(deltaTime);
    }
}

void gui::scenes::Game::draw(UNUSED gui::ILibrary& lib)
{
    auto size = _gameData->map().size();
    for (uint32_t y = 0; y < size.y(); y++) {
        for (uint32_t x = 0; x < size.x(); x++) {
            _gameData->map().at({x, y})->draw(lib);
        }
    }

    for (auto& player : _gameData->players()) {
        player->drawAnimation(lib);
    }
    for (auto& egg : _gameData->eggs()) {
        egg->drawAnimation(lib);
    }
}

void gui::scenes::Game::onEnter(UNUSED IScene::State lastState, UNUSED gui::ILibrary& lib)
{
    if (lastState == IScene::State::LOADING) {
        _tickTime = 1 / static_cast<float>(_gameData->timeUnit());
        std::cout << "Tick time: " << _tickTime << std::endl;

        auto mapSize = _gameData->map().size();
        std::shared_ptr<gui::Tile> tile;
        for (uint32_t y = 0; y < mapSize.y(); y++) {
            for (uint32_t x = 0; x < mapSize.x(); x++) {
                tile = _gameData->map().at({x, y});
                tile->setOffset({static_cast<float>(x * 120), static_cast<float>(y * 120)});
                for (auto& player : tile->entities()) {
                    player->setTileDisplayOffset(tile->offset());
                }
            }
        }
    }
}

void gui::scenes::Game::onExit(UNUSED IScene::State nextState, UNUSED gui::ILibrary& lib)
{
}


