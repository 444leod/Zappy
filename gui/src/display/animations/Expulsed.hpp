/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Expulsed
*/

#pragma once

#include "AAnimation.hpp"
#include "Player.hpp"

namespace gui::animations {
    class Expulsed : public AAnimation {
        public:
            Expulsed(const std::string& skin, std::shared_ptr<gui::Player> player);
            ~Expulsed();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            std::string _skin;
            std::shared_ptr<gui::Player> _player;
            Vector2f _direction;
    };
}

