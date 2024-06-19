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
    lib.display().setWidth(1920);
    lib.display().setHeight(1080);

    gui::FontSpecification text {
           .color = gui::Color {200, 200, 200, 255},
           .size = 32,
           .path = "gui/ressources/fonts/ClashRoyale.ttf"
       };
   lib.fonts().load("ClashRoyale", text);
   std::cout << "Loaded ClashRoyale font" << std::endl;

    for (auto& scene : _scenes)
        scene.second->initialize(lib);
}

void gui::SceneManager::onKeyPressed(gui::ILibrary& lib, gui::KeyCode key, bool shift)
{
    _scenes[_currentState]->onKeyPressed(lib, key, shift);
}

void gui::SceneManager::onMouseButtonPressed(gui::ILibrary& lib, gui::MouseButton button, int32_t x, int32_t y)
{
    _scenes[_currentState]->onMouseButtonPressed(lib, button, x, y);
}

void gui::SceneManager::update(gui::ILibrary& lib, float deltaTime)
{
    if (_currentState != _previousState) {
        _scenes[_previousState]->onExit(_currentState, lib);
        _scenes[_currentState]->onEnter(_previousState, lib);
        _previousState = _currentState;
    }
    _scenes[_currentState]->update(lib, deltaTime);
}

void gui::SceneManager::draw(gui::ILibrary& lib)
{
    lib.display().clear();
    _scenes[_currentState]->draw(lib);
    lib.display().flush();
}


