/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Seg
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Seg : public ICommand {
        public:
            /**
             * @brief The command seg sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command seg receives when the server send the end of the game for a team
             * @note Receives the command: seg N
             * @note N -> team name
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
