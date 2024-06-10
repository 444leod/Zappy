/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Msz
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Msz : public ACommand {
        public:
            void send() override;
            void receive(std::string command, GameData &gameData) override;

        private:
    };
}
