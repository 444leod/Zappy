/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tna
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Tna : public ICommand {
        public:
            /**
             * @brief The command tna send simply "tna" to the server and expect the name of the teams
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command tna receive the name of the teams
             * @note Receive the command: tna N
             * @note N -> name of the team
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
