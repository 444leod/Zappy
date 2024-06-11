/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pic
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Pic : public ACommand {
        public:
            void stage(ntw::Client &client, std::string parameters = "") override;
            void receive(std::string command, GameData &gameData) override;
    };
}
