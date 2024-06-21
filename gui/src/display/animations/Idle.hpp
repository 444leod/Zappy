/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Idle
*/

#pragma once

#include "AAnimation.hpp"
#include "Player.hpp"

namespace gui::animations {
    class Idle : public AAnimation {
        public:
            Idle(const std::string& skin, gui::Player& player, float duration = 10.f, uint32_t frameCount = 5);
            ~Idle();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;
            float remainingTime() override;

        protected:
        private:
            std::string _skin;
            gui::Player& _player;
    };
}
