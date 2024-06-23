/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Loading
*/

#pragma once

#include "ILibrary.hpp"
#include "GameData.hpp"
#include "../IScene.hpp"

namespace gui {
    namespace scenes {
        class Loading : public IScene {
            public:
                Loading(State& state, std::shared_ptr<gui::GameData> gameData, std::shared_ptr<ntw::Client> serverCli) : IScene(state, gameData, serverCli) {};
                ~Loading() = default;

                void initialize(gui::ILibrary& lib) override;
                void onKeyPressed(gui::ILibrary& lib, gui::KeyCode key, bool shift) override;
                void onKeyDown(gui::ILibrary& lib, gui::KeyCode key) override;
                void onMouseButtonPressed(gui::ILibrary& lib, gui::MouseButton button, int32_t x, int32_t y) override;
                void update(gui::ILibrary& lib, float deltaTime) override;
                void draw(gui::ILibrary& lib) override;
                void onEnter(IScene::State lastState, gui::ILibrary& lib) override;
                void onExit(IScene::State nextState, gui::ILibrary& lib) override;

            private:
                std::string _loadingText = "Loading...";
                std::pair<bool, std::vector<std::string>> _teamNames = {false, {}};
        };
    }
}
