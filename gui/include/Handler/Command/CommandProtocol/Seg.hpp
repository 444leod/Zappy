/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Seg
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Seg : public ACommand {
        public:
            void send() override;
            void receive(std::string command, GameData &gameData) override;

        protected:
        private:
    };
}
