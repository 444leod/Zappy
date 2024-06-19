/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Loading
*/

#include "Loading.hpp"
#include "Tna.hpp"
#include "Msz.hpp"

void gui::scenes::Loading::initialize(UNUSED gui::ILibrary& lib)
{
}

void gui::scenes::Loading::onKeyPressed(UNUSED gui::ILibrary& lib, UNUSED gui::KeyCode key, UNUSED bool shift)
{
}

void gui::scenes::Loading::onMouseButtonPressed(UNUSED gui::ILibrary& lib, UNUSED gui::MouseButton button, UNUSED int32_t x, UNUSED int32_t y)
{
}

void gui::scenes::Loading::update(UNUSED gui::ILibrary& lib, UNUSED float deltaTime)
{
    static float passedTime = 0;
    passedTime += deltaTime;
    if (passedTime > 0.6) {
        if (_loadingText.size() == 11)
            _loadingText = "Loading";
        else
            _loadingText += ".";
        passedTime -= 1;
    }

    if (_gameData->mapRef().mapSize() == Vector2u(0, 0)) {
        static float mapSizePassedTime = 0;
        static uint8_t mapSizeTries = 0;
        mapSizePassedTime += deltaTime;
        if (mapSizeTries == 0 || mapSizePassedTime > 5) {
            mapSizeTries++;
            if (mapSizeTries > 3)
                throw gui::ntw::Client::ClientException("Server took too long to respond");
            Msz().stage(_serverCli);
            mapSizePassedTime = 0;
        }
    }

    if (_gameData->teamNames().size() == 0) {
        static float teamNamesPassedTime = 0;
        static uint8_t teamNameTries = 0;
        teamNamesPassedTime += deltaTime;
        if (teamNameTries == 0 || teamNamesPassedTime > 5) {
            teamNameTries++;
            if (teamNameTries > 3)
                throw gui::ntw::Client::ClientException("Server took too long to respond");
            Tna().stage(_serverCli);
            teamNamesPassedTime = 0;
        }
    }
}

void gui::scenes::Loading::draw(UNUSED gui::ILibrary& lib)
{
    auto size = lib.display().measure(_loadingText, lib.fonts().get("ClashRoyale"), lib.display().width(), lib.display().height()).width;
    float center = lib.display().width() / 2 - size / 2;
    lib.display().print(_loadingText, lib.fonts().get("ClashRoyale"), center, lib.display().height() / 2);

    auto teamNames = _gameData->teamNames();

    float y = 0;
    auto mapSize = _gameData->mapRef().mapSize();

    if (mapSize != Vector2u(0, 0)) {
        lib.display().print("Map size: " + std::to_string(mapSize.x()) + "x" + std::to_string(mapSize.y()), lib.fonts().get("ClashRoyale"), 0, y);
        y += 50;
    }
    if (teamNames.size() != 0) {
        for (auto &teamName : _gameData->teamNames()) {
            lib.display().print(teamName, lib.fonts().get("ClashRoyale"), 0, y);
            y += 50;
        }
    }
}

void gui::scenes::Loading::onEnter(UNUSED IScene::State lastState, UNUSED gui::ILibrary& lib)
{
}

void gui::scenes::Loading::onExit(UNUSED IScene::State nextState, UNUSED gui::ILibrary& lib)
{
}

