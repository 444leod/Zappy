/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ACommand
*/

#pragma once

#include "ICommand.hpp"
#include <sstream>

namespace gui {
    class ACommand : public ICommand {
        public:
            virtual void stage(ntw::Client &client, std::string command) = 0;
            virtual void receive(std::string command, GameData &gameData) = 0;
    };
}
