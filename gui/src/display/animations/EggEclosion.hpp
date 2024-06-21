/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** EggEclosion
*/

#pragma once

#include "AAnimation.hpp"
#include "Egg.hpp"

namespace gui::animations {
    class EggEclosion : public AAnimation {
        public:
            EggEclosion(const std::string& skin, std::shared_ptr<gui::Egg> egg);
            ~EggEclosion();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            std::string _skin;
            std::shared_ptr<gui::Egg> _egg;
            Vector2f _direction;
    };
}

