/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Suc
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Suc : public ICommand {
        public:
            /**
             * @brief The command Suc send nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Suc receive when the server send an unknown command
             * @note Receive the command: suc
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
