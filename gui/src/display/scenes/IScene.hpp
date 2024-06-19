/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IScene
*/

#pragma once

#include "ILibrary.hpp"
#include "GameData.hpp"
#include "Client.hpp"

namespace gui {
    class IScene {
        public:
            static enum class State {
                LOADING,
                GAME
            } _state;

            IScene(State &state, std::shared_ptr<gui::GameData> gameData, std::shared_ptr<ntw::Client> serverCli) : _currentState(state), _gameData(gameData), _serverCli(serverCli) {};
            ~IScene() =  default;

            virtual void initialize(gui::ILibrary& lib) = 0;
            virtual void onKeyPressed(gui::ILibrary& lib, gui::KeyCode key, bool shift) = 0;
            virtual void onMouseButtonPressed(gui::ILibrary& lib, gui::MouseButton button, int32_t x, int32_t y) = 0;
            virtual void update(gui::ILibrary& lib, float deltaTime) = 0;
            virtual void draw(gui::ILibrary& lib) = 0;
            virtual void onEnter(IScene::State lastState, gui::ILibrary& lib) = 0;
            virtual void onExit(IScene::State nextState, gui::ILibrary& lib) = 0;

        protected:
            State& _currentState;
            std::shared_ptr<gui::GameData> _gameData;
            std::shared_ptr<ntw::Client> _serverCli;
        private:
    };
}
