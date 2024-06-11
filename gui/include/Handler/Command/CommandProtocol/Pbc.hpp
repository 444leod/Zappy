/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pbc
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Pbc : public ACommand {
        public:
            /**
             * @brief Stage the command
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief Receive the command
             * @param command The command
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
