/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Game
*/

#pragma once

#include "ILibrary.hpp"
#include "GameData.hpp"
#include "../IScene.hpp"

namespace gui {
    namespace scenes {
        class Game : public IScene {
            public:
                Game(State& state, std::shared_ptr<gui::GameData> gameData, std::shared_ptr<ntw::Client> serverCli) : IScene(state, gameData, serverCli) {};
                ~Game() = default;

                void initialize(gui::ILibrary& lib) override;
                void onKeyPressed(gui::ILibrary& lib, gui::KeyCode key, bool shift) override;
                void onKeyDown(gui::ILibrary& lib, gui::KeyCode key) override;
                void onMouseButtonPressed(gui::ILibrary& lib, gui::MouseButton button, int32_t x, int32_t y) override;
                void update(gui::ILibrary& lib, float deltaTime) override;
                void draw(gui::ILibrary& lib) override;
                void onEnter(IScene::State lastState, gui::ILibrary& lib) override;
                void onExit(IScene::State nextState, gui::ILibrary& lib) override;

            private:
                void _displayMap(gui::ILibrary& lib);
                void _displayOverlay(gui::ILibrary& lib);
                void _updateTilePos(gui::ILibrary& lib, gui::KeyCode key);
                void _displayMessages(gui::ILibrary& lib);
                void _displayGlobalInformations(gui::ILibrary& lib);
                void _displayTileInformations(gui::ILibrary& lib);

            public:
            private:
                gui::Vector2i _rightTopCornerOffset = {0, 0};
                float _tickTime = 0;
                uint32_t _passedTicks = 0;
                bool _gameInfo = false;
                gui::Vector2u _tileInfo = {0, 0};
                bool _areMessagesDisplayed = false;
        };
    }
}
