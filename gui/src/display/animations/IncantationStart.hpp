/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IncantationStart
*/

#pragma once

#include "AAnimation.hpp"
#include "Player.hpp"

namespace gui::animations {
    class IncantationStart : public AAnimation {
        public:
            IncantationStart(const std::string& skin, std::shared_ptr<gui::Player> player);
            ~IncantationStart();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            std::string _skin;
            std::shared_ptr<gui::Player> _player;
            Vector2f _direction;
    };
}

