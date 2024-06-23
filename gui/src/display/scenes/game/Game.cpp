/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/

#include "Game.hpp"
#include "Ppo.hpp"
#include "Mct.hpp"
#include "SkinsConfig.hpp"

const std::map<gui::KeyCode, gui::Vector2f> KEY_TO_OFFSET = {
    {gui::KeyCode::UP, {0, 1}},
    {gui::KeyCode::DOWN, {0, -1}},
    {gui::KeyCode::LEFT, {1, 0}},
    {gui::KeyCode::RIGHT, {-1, 0}}
};

void gui::scenes::Game::initialize(UNUSED gui::ILibrary& lib)
{
    gui::TextureSpecification spec;
    spec.graphical.subrect = {0, 0, 122, 132};

        //TODO: add egg sprite and egg spawn on launch

    uint32_t frameIndex = 0;
    for (auto [skin, file] : gui::skins::SKIN_TO_FILE) {
        spec.graphical.path = "gui/assets/" + file;
        for (auto [animation, frames] : gui::skins::ANIMATIONS_FRAMES[skin]) {
            for (uint8_t i = 0; i < frames; i++) {
                spec.graphical.subrect->x = i * 122;
                spec.graphical.subrect->y = frameIndex * 132;
                lib.textures().load(gui::skins::SKIN_TO_STRING[skin] + gui::skins::ANIMATION_TO_STRING[animation] + std::to_string(i), spec);
            }
            frameIndex++;
        }
        for (auto [static_sprite, coords] : gui::skins::STATIC_SPRITES_POSITION[skin]) {
            spec.graphical.subrect->x = coords.second * 122;
            spec.graphical.subrect->y = coords.first * 132;
            lib.textures().load(gui::skins::SKIN_TO_STRING[skin] + gui::skins::STATIC_SPRITES_TO_STRING[static_sprite], spec);
        }
        frameIndex = 0;
    }

    spec.graphical.path = "gui/assets/map_sprite_sheet.png";
    spec.graphical.subrect = {8071, 2014, 220, 220};
    lib.textures().load("grass", spec);
}

void gui::scenes::Game::_updateTilePos(UNUSED gui::ILibrary& lib, UNUSED gui::KeyCode key)
{
    auto offset = KEY_TO_OFFSET.at(key);
    for (auto& [coords, tile] : _gameData->map().tiles())
        tile->setOffset(tile->offset() + offset * 5);
}

void gui::scenes::Game::onKeyPressed(gui::ILibrary& lib, gui::KeyCode key, UNUSED bool shift)
{
    switch (key) {
        case gui::KeyCode::LEFT:
            if (_gameData->map().at(Vector2u{0, 0})->offset().x() >= 0)
                break;
            this->_updateTilePos(lib, key);
            break;
        case gui::KeyCode::RIGHT:
            if (_gameData->map().at(Vector2u{_gameData->map().size().x() - 1, 0})->offset().x() <= 1100)
                break;
            this->_updateTilePos(lib, key);
            break;
        case gui::KeyCode::UP:
            if (_gameData->map().at(Vector2u{0, 0})->offset().y() >= 0)
                break;
            this->_updateTilePos(lib, key);
            break;
        case gui::KeyCode::DOWN:
            if (_gameData->map().at(Vector2u{0, _gameData->map().size().y() - 1})->offset().y() <= 770)
                break;
            this->_updateTilePos(lib, key);
            break;
        case gui::KeyCode::SPACE:
        {
            for (auto& [coords, tile] : _gameData->map().tiles()) {
                tile->setOffset({static_cast<float>(coords.x() * 120), static_cast<float>(coords.y() * 120)});
            }
            break;
        }
        default:
            break;
    }
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
        for (auto& player : _gameData->players()) {
            Ppo().stage(_serverCli, std::to_string(player->id()));
        }

        if (_passedTicks != 0 && _passedTicks % 10 == 0) {
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
    for (auto& [coords, tile] : _gameData->map().tiles())
        tile->draw(lib);

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

        auto mapSize = _gameData->map().size();
        std::shared_ptr<gui::Tile> tile;
        for (auto& [coords, tile] : _gameData->map().tiles())
            tile->setOffset({static_cast<float>(coords.x() * 120), static_cast<float>(coords.y() * 120)});
    }
}

void gui::scenes::Game::onExit(UNUSED IScene::State nextState, UNUSED gui::ILibrary& lib)
{
}


