/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

void gui::SceneManager::initialize(gui::ILibrary& lib)
{
    lib.display().setTitle("Zappy GUI");
    lib.display().setFramerate(60);
    lib.display().setWidth(1600);
    lib.display().setHeight(900);

    gui::FontSpecification text {
           .color = gui::Color {200, 200, 200, 255},
           .size = 20,
           .path = "gui/ressources/fonts/ClashRoyale.ttf"
       };
   lib.fonts().load("ClashRoyale", text);

    _scenes = {
        {gui::IScene::State::LOADING, std::make_shared<gui::scenes::Loading>(_currentState, _gameData, _serverCli)},
        {gui::IScene::State::GAME, std::make_shared<gui::scenes::Game>(_currentState, _gameData, _serverCli)}
    };

    for (auto& scene : _scenes)
        scene.second->initialize(lib);
}

void gui::SceneManager::onKeyPressed(gui::ILibrary& lib, gui::KeyCode key, bool shift)
{
    _scenes[_currentState]->onKeyPressed(lib, key, shift);
}

void gui::SceneManager::onKeyDown(gui::ILibrary& lib, gui::KeyCode key)
{
    _scenes[_currentState]->onKeyDown(lib, key);
}

void gui::SceneManager::onMouseButtonPressed(gui::ILibrary& lib, gui::MouseButton button, int32_t x, int32_t y)
{
    _scenes[_currentState]->onMouseButtonPressed(lib, button, x, y);
}

void gui::SceneManager::update(gui::ILibrary& lib, float deltaTime)
{
    _scenes[_currentState]->update(lib, deltaTime);
    if (_currentState != _previousState) {
        if (_scenes.find(_previousState) == _scenes.end() || _scenes.find(_currentState) == _scenes.end())
            throw std::runtime_error("Scene not found");
        _scenes[_previousState]->onExit(_currentState, lib);
        _scenes[_currentState]->onEnter(_previousState, lib);
        _previousState = _currentState;
    }
}

void gui::SceneManager::draw(gui::ILibrary& lib)
{
    lib.display().clear();
    _scenes[_currentState]->draw(lib);
    lib.display().flush();
}


