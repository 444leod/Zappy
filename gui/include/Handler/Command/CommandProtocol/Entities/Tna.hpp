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
             * @brief The command tna sends simply "tna" to the server and expect the name of the teams
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command tna receives the name of the teams
             * @note Receives the command: tna N
             * @note N -> name of the team
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
