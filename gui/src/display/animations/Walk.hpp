/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Walk
*/

#pragma once

#include "AAnimation.hpp"
#include "Player.hpp"

namespace gui::animations {
    class Walk : public AAnimation {
        public:
            Walk(const std::string& skin, std::shared_ptr<gui::Player> player);
            ~Walk();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            std::string _skin;
            std::shared_ptr<gui::Player> _player;
            Vector2f _direction;
    };
}

