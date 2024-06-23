/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Loading
*/

#include "Loading.hpp"
#include "Tna.hpp"
#include "Msz.hpp"
#include "Mct.hpp"
#include "Sgt.hpp"
#include "Pnw.hpp"
#include "CommandHandler.hpp"

void gui::scenes::Loading::initialize(UNUSED gui::ILibrary& lib)
{
    SoundSpecification spec;
    spec.path = "gui/assets/audio/HEHEHEHA.wav";
    lib.sounds().load("HIHIHIHA", spec);

    spec.path = "gui/assets/audio/start.wav";
    lib.sounds().load("start", spec);
}

void gui::scenes::Loading::onKeyDown(UNUSED gui::ILibrary& lib, UNUSED gui::KeyCode key)
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
    if (_gameData->map().size() == Vector2u(0, 0)) {
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

    if (_gameData->timeUnit() == 0) {
        static float timeUnitPassedTime = 0;
        static uint8_t timeUnitTries = 0;
        timeUnitPassedTime += deltaTime;
        if (timeUnitTries == 0 || timeUnitPassedTime > 5) {
            timeUnitTries++;
            if (timeUnitTries > 3)
                throw gui::ntw::Client::ClientException("Server took too long to respond");
            Sgt().stage(_serverCli);
            timeUnitPassedTime = 0;
        }
    }

    if (_gameData->map().size() != Vector2u(0, 0) && _gameData->teamNames().size() != 0 && _gameData->timeUnit() != 0) {
        static float fullLoadingPassedTime = 0;
        fullLoadingPassedTime += deltaTime;
        if (fullLoadingPassedTime > 3) {
            auto playerConnexionQueue = _gameData->map().playerConnexionQueue();
            while (!playerConnexionQueue.empty()) {
                Pnw().receive(playerConnexionQueue.front(), _gameData);
                playerConnexionQueue.pop();
            }
            _currentState = IScene::State::GAME;
        }
        _loadingText = "Launching game...";
    } else {
        static float passedTime = 0;
        passedTime += deltaTime;
        if (passedTime > 0.6) {
            if (_loadingText.size() == 11)
                _loadingText = "Loading";
            else
                _loadingText += ".";
            passedTime -= 1;
        }
    }
}

void gui::scenes::Loading::draw(UNUSED gui::ILibrary& lib)
{
    static bool first = true;

    if (first) {
        lib.sounds().play("start", 50.f);
        first = false;
    }
    auto font = lib.fonts().get("ClashRoyale");
    auto textSize = lib.display().measure(_loadingText, font, lib.display().width(), lib.display().height()).width;
    float center = lib.display().width() / 2 - textSize / 2;
    lib.display().print(_loadingText, font, center, lib.display().height() / 2);

    auto teamNames = _gameData->teamNames();

    float y = 0;
    auto size = _gameData->map().size();

    if (size != Vector2u(0, 0)) {
        lib.display().print("Map size: " + std::to_string(size.x()) + "x" + std::to_string(size.y()), font, 0, y);
        y += 50;
    }
    if (teamNames.size() != 0) {
        for (auto &teamName : _gameData->teamNames()) {
            lib.display().print(teamName, font, 0, y);
            y += 50;
        }
    }
    if (_gameData->timeUnit() != 0) {
        lib.display().print("Time unit: " + std::to_string(_gameData->timeUnit()), font, 0, y);
        y += 50;
    }
}

void gui::scenes::Loading::onEnter(UNUSED IScene::State lastState, UNUSED gui::ILibrary& lib)
{
}

void gui::scenes::Loading::onExit(UNUSED IScene::State nextState, UNUSED gui::ILibrary& lib)
{
    gui::CommandHandler::isLoaded = true;
    if (nextState == IScene::State::GAME)
        Mct().stage(_serverCli);
}

