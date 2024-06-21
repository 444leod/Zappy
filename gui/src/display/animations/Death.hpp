/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Death
*/

#pragma once

#include "AAnimation.hpp"
#include "Player.hpp"

namespace gui::animations {
    class Death : public AAnimation {
        public:
            Death(const std::string& skin, std::shared_ptr<gui::Player> player);
            ~Death();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            std::string _skin;
            std::shared_ptr<gui::Player> _player;
    };
}

