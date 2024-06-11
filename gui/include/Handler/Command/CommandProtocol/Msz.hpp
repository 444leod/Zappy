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
            void stage(ntw::Client &client, std::string command) override;
            void receive(std::string command, GameData &gameData) override;

        private:
    };
}
