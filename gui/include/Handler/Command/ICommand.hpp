/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ICommand
*/

#pragma once

#include <iostream>
#include <vector>
#include "GameData.hpp"

namespace gui {
    class ICommand {
        public:
            ICommand() = default;
            ~ICommand() = default;

            virtual void send() = 0;
            virtual void receive(std::string command, GameData &gameData) = 0;
    };
}
