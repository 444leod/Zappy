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
    spec.graphical.subrect = {0, 0, 152, 173};

    std::vector<std::pair<std::string, std::uint8_t>> _frames = {
        {"bowler_eject_south_", 13},
        {"bowler_eject_west_", 13},
        {"bowler_eject_east_", 13},
        {"bowler_eject_north_", 13},
        {"bowler_walk_south_", 13},
        {"bowler_walk_west_", 13},
        {"bowler_walk_east_", 13},
        {"bowler_walk_north_", 13},
        {"bowler_idle_", 12}
    };

    for (uint8_t frameIndex = 0; frameIndex < _frames.size(); frameIndex++) {
        std::string name = _frames[frameIndex].first;
        uint8_t frameCount = _frames[frameIndex].second;
        for (uint8_t i = 0; i < frameCount; i++) {
            spec.graphical.subrect->x = i * 152;
            spec.graphical.subrect->y = frameIndex * 173;
            lib.textures().load(name + std::to_string(i), spec);
        }
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


