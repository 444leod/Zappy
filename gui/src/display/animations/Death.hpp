/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Death
*/

#pragma once

#include "AAnimation.hpp"
#include "Player.hpp"
#include "GameData.hpp"

namespace gui::animations {
    class Death : public AAnimation {
        public:
            Death(gui::Player& player, std::shared_ptr<gui::GameData> gameData);
            ~Death();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            gui::Player& _player;
            std::shared_ptr<gui::GameData> _gameData;
            float _scale = 0.5f;
            std::string _skin;
            Vector2f _pos;
    };
}

