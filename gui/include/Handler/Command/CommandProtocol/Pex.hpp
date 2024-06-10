/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pex
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Pex : public ACommand {
        public:
            void send() override;
            void receive(std::string command, GameData &gameData) override;

        protected:
        private:
    };
}
