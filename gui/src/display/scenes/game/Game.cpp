/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/

#include "Game.hpp"
#include "Ppo.hpp"
#include "Pin.hpp"
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
    gui::MusicSpecification musicSpec;
    musicSpec.path = "gui/assets/audio/coc_music.wav";
    musicSpec.loop = true;
    lib.musics().load("game_music", musicSpec);

    gui::SoundSpecification soundSpec;
    soundSpec.path = "gui/assets/audio/win.wav";
    lib.sounds().load("win", soundSpec);
    soundSpec.path = "gui/assets/audio/draw.wav";
    lib.sounds().load("draw", soundSpec);

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

    spec.graphical.path = "gui/assets/consumable_sprite_sheet.png";
    spec.graphical.subrect = {0, 0, 23, 24};

    std::vector<std::pair<std::string, uint8_t>> consumables = {
        {"linemate", 0},
        {"deraumere", 1},
        {"sibur", 2},
        {"mendiane", 3},
        {"phiras", 4},
        {"thystame", 5},
        {"food", 6}
    };

    for (auto& [consumable, index] : consumables) {
        spec.graphical.subrect->x = 24;
        spec.graphical.subrect->y = index * 23;
        lib.textures().load(consumable, spec);
    }

}

void gui::scenes::Game::_updateTilePos(UNUSED gui::ILibrary& lib, UNUSED gui::KeyCode key)
{
    auto offset = KEY_TO_OFFSET.at(key);
    for (auto& [coords, tile] : _gameData->map().tiles())
        tile->setOffset(tile->offset() + offset * 5);
}

void gui::scenes::Game::onKeyDown(UNUSED gui::ILibrary& lib, gui::KeyCode key)
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
        default:
            break;
    }
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
                tile->setOffset({static_cast<float>(coords.x() * 114), static_cast<float>(coords.y() * 114)});
            }
            break;
        }
        case gui::KeyCode::ESCAPE:
            _gameInfo = false;
            break;
        case gui::KeyCode::M:
            this-> _areMessagesDisplayed = !this->_areMessagesDisplayed;
            break;
        default:
            break;
    }
}

void gui::scenes::Game::onMouseButtonPressed(UNUSED gui::ILibrary& lib, gui::MouseButton button, int32_t x, int32_t y)
{
    if (button == gui::MouseButton::LEFT && ((_gameData->map().size().x() * 114) > static_cast<uint32_t>(x) && (_gameData->map().size().y() * 114) > static_cast<uint32_t>(y))) {
        auto firstTile = _gameData->map().at(Vector2u{0, 0});
        x -= firstTile->offset().x();
        y -= firstTile->offset().y();
        auto tilePos = gui::Vector2u(static_cast<unsigned int>(x / 114), static_cast<unsigned int>(y / 114));
        _tileInfo = tilePos;
        _gameInfo = true;
    }
    if (button == gui::MouseButton::LEFT && ((_gameData->map().size().x() * 114) < static_cast<uint32_t>(x) || (_gameData->map().size().y() * 114) < static_cast<uint32_t>(y))) {
        _gameInfo = false;
    }
}

void gui::scenes::Game::update(UNUSED gui::ILibrary& lib, float deltaTime)
{
    static float passedTime = 0;
    passedTime += deltaTime;

    if (passedTime >= _tickTime) {
        _passedTicks++;
        passedTime -= _tickTime;
        for (auto& player : _gameData->players()) {
            if (!player->alive())
                continue;
            Ppo().stage(_serverCli, std::to_string(player->id()));
            Pin().stage(_serverCli, std::to_string(player->id()));
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

    static uint32_t messageLength = 0;
    if (messageLength != _gameData->messages().size()) {
        messageLength = _gameData->messages().size();
        lib.sounds().play("HIHIHIHA", 20.f);
    }
}

void gui::scenes::Game::_displayMessages(gui::ILibrary& lib)
{
    if (!this->_areMessagesDisplayed)
        return;
    lib.display().print("Broadcasts: ", lib.fonts().get("ClashRoyale"), 1200, 750, gui::Color{255, 255, 255, 255}, 12);

    size_t messagesCount = _gameData->messages().size();
    size_t startIdx = messagesCount > 10 ? messagesCount - 10 : 0;

    for (size_t i = startIdx; i < messagesCount; ++i) {
        const auto message = _gameData->messages()[i];
        std::string displayedMessage = message.message.substr(0, 50);

        std::string msg;
        msg.reserve(50);
        msg += "Player ";
        msg += std::to_string(message.senderId);
        msg += ": ";
        msg += displayedMessage;

        lib.display().print(msg, lib.fonts().get("ClashRoyale"), 1210, 765 + static_cast<int>(i - startIdx) * 10, gui::Color{255, 255, 255, 255}, 8);
    }
}

void gui::scenes::Game::_displayGlobalInformations(gui::ILibrary& lib)
{
    auto teamNames = _gameData->teamNames();
    uint32_t i = 0;

    lib.display().print("Time: " + std::to_string(_passedTicks), lib.fonts().get("ClashRoyale"), 1200, 10, gui::Color{255, 255, 255, 255}, 12);
    lib.display().print("Number of Players: " + std::to_string(_gameData->players().size()), lib.fonts().get("ClashRoyale"), 1200, 30, gui::Color{255, 255, 255, 255}, 12);
    lib.display().print("Number of Teams: " + std::to_string(teamNames.size()), lib.fonts().get("ClashRoyale"), 1200, 50, gui::Color{255, 255, 255, 255}, 12);

    for (auto& teamName : teamNames) {
        auto [skinName, color] = _gameData->teamSkin(teamName);
        lib.display().print(" - \"" + teamName + "\" (" + skinName + ")",  lib.fonts().get("ClashRoyale"), 1200, 70 + i * 20, color, 12);
        i++;
    }
}

void gui::scenes::Game::_displayTileInformations(gui::ILibrary& lib)
{
    auto tile = _gameData->map().at(_tileInfo);
    uint32_t i = 0;
    bool hasPrinted = false;

    lib.display().print("Tile " + std::to_string(_tileInfo.x()) + ", " + std::to_string(_tileInfo.y()) + ":" , lib.fonts().get("ClashRoyale"), 1300, 10, gui::Color{255, 255, 255, 255}, 20);
    std::uint32_t index = 0;
    for (auto& entity : tile->entities()) {
        index++;
        if (index >= 10)
            break;
        if (entity->type() == gui::AEntity::EntityType::PLAYER) {
            auto player = std::dynamic_pointer_cast<gui::Player>(entity);
            std::string displayedText = "Player ";
            displayedText += std::to_string(entity->id());
            displayedText += " {";
            displayedText += std::to_string(player->level());
            displayedText += "} ";
            displayedText += std::to_string(player->food());
            displayedText += " ";
            displayedText += std::to_string(player->rocks().linemate.quantity());
            displayedText += " ";
            displayedText += std::to_string(player->rocks().deraumere.quantity());
            displayedText += " ";
            displayedText += std::to_string(player->rocks().sibur.quantity());
            displayedText += " ";
            displayedText += std::to_string(player->rocks().mendiane.quantity());
            displayedText += " ";
            displayedText += std::to_string(player->rocks().phiras.quantity());
            displayedText += " ";
            displayedText += std::to_string(player->rocks().thystame.quantity());

            lib.display().print(displayedText, lib.fonts().get("ClashRoyale"), 1200, 50 + i * 20, _gameData->teamSkin(entity->teamName()).second, 15);
        } else {
            lib.display().print("Egg " + std::to_string(entity->id()), lib.fonts().get("ClashRoyale"), 1200, 50 + i * 20, gui::Color{255, 255, 255, 255}, 15);
        }
        i++;
    }
     if (hasPrinted)
        i++;
    auto printItem = [&](const std::string& itemName, auto& item, gui::Color color) {
        if (item.quantity()) {
            lib.display().print(itemName + ": " + std::to_string(item.quantity()), lib.fonts().get("ClashRoyale"), 1200, 70 + i * 20, color, 15);
            i++;
        }
    };
    if (tile->food()) {
        lib.display().print("food: " + std::to_string(tile->food()), lib.fonts().get("ClashRoyale"), 1200, 70 + i * 20, gui::Color{255, 215, 0, 255}, 15);
        i++;
    }
    printItem("linemate", tile->rocks().linemate, gui::Color{0, 100, 255, 255});
    printItem("deraumere", tile->rocks().deraumere, gui::Color{255, 105, 180, 255});
    printItem("sibur", tile->rocks().sibur, gui::Color{0, 100, 0, 255});
    printItem("mendiane", tile->rocks().mendiane, gui::Color{255, 0, 0, 255});
    printItem("phiras", tile->rocks().phiras, gui::Color{255, 255, 0, 255});
    printItem("thystame", tile->rocks().thystame, gui::Color{144, 238, 144, 255});
}

void gui::scenes::Game::_displayMap(gui::ILibrary& lib)
{
    for (auto& [coords, tile] : _gameData->map().tiles())
        tile->draw(lib);
    for (auto& egg : _gameData->eggs()) {
        egg->drawAnimation(lib);
    }
    for (auto& player : _gameData->players()) {
        player->drawAnimation(lib);
    }
}

void gui::scenes::Game::_displayOverlay(gui::ILibrary& lib)
{
    if (!_gameInfo) {
        _displayGlobalInformations(lib);
    } else {
        _displayTileInformations(lib);
    }

    _displayMessages(lib);
}

void gui::scenes::Game::draw(gui::ILibrary& lib)
{
    _displayMap(lib);
    _displayOverlay(lib);
}

void gui::scenes::Game::onEnter(IScene::State lastState, UNUSED gui::ILibrary& lib)
{
    if (lastState == IScene::State::LOADING) {
        lib.musics().play("game_music", 50.f);
        _tickTime = 1 / static_cast<float>(_gameData->timeUnit());

        auto mapSize = _gameData->map().size();
        std::shared_ptr<gui::Tile> tile;
        for (auto& [coords, tile] : _gameData->map().tiles())
            tile->setOffset({static_cast<float>(coords.x() * 114), static_cast<float>(coords.y() * 114)});
    }
}

void gui::scenes::Game::onExit(UNUSED IScene::State nextState, UNUSED gui::ILibrary& lib)
{
}


