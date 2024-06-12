/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sbp
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Sbp : public ICommand {
        public:
            /**
             * @brief The command sbp send nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command sbp receive when the server send a bad command
             * @note Receive the command: sbp
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
