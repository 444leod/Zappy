/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Smg
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Smg : public ICommand {
        public:
            /**
             * @brief The command Smg send nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Smg receive when the server send a message
             * @note Receive the command: smg M
             * @note M -> message
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
