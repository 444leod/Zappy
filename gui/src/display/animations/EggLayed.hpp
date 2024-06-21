/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** EggLayed
*/

#pragma once

#include "AAnimation.hpp"
#include "Egg.hpp"

namespace gui::animations {
    class EggLayed : public AAnimation {
        public:
            EggLayed(const std::string& skin, std::shared_ptr<gui::Egg> egg);
            ~EggLayed();

            void update(float deltaTime) override;
            void draw(gui::ILibrary& lib) override;

        protected:
        private:
            std::string _skin;
            std::shared_ptr<gui::Egg> _egg;
            Vector2f _direction;
    };
}

