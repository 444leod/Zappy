/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** SceneManager
*/

#pragma once

#include "IScene.hpp"
#include "loading/Loading.hpp"
#include "game/Game.hpp"

namespace gui {
    class SceneManager {
        public:
            SceneManager(std::shared_ptr<gui::GameData> gameData, std::shared_ptr<gui::ntw::Client> serverCli) : _gameData(gameData), _serverCli(serverCli) {}
            ~SceneManager() = default;

            void initialize(gui::ILibrary& lib);
            void onKeyPressed(gui::ILibrary& lib, gui::KeyCode key, bool shift);
            void onMouseButtonPressed(gui::ILibrary& lib, gui::MouseButton button, int32_t x, int32_t y);
            void update(gui::ILibrary& lib, float deltaTime);
            void draw(gui::ILibrary& lib);
        protected:
        private:
            std::shared_ptr<gui::GameData> _gameData;
            std::shared_ptr<gui::ntw::Client> _serverCli;

            gui::IScene::State _previousState = gui::IScene::State::LOADING;
            gui::IScene::State _currentState = gui::IScene::State::LOADING;

            std::map<gui::IScene::State, std::shared_ptr<gui::IScene>> _scenes;
    };
}
