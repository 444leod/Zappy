/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sgt
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Sgt : public ICommand {
        public:
            /**
             * @brief the command Sgt send simply "sgt" to the server to get the time unit
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Sgt receive when the server send the time unit
             * @note Receive the command: sgt T
             * @note T -> time unit
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
