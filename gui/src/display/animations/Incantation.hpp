/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Incantation
*/

#pragma once

#include "AAnimation.hpp"
#include "Player.hpp"

namespace gui {
    class Player;
}

namespace gui::animations {

    class Incantation : public AAnimation {
        public:
            Incantation(gui::Player& player);
            ~Incantation();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            std::string _skin;
            gui::Player& _player;
    };
}

