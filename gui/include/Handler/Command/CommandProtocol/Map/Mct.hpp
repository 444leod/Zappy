/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Mct
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Mct : public ICommand {
        public:
            /**
             * @brief The command Mct sends simply "mct" to the server and expect the map
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Mct receives the map
             * @note Receives the command: bct X Y q0 q1 q2 q3 q4 q5 q6 * nbr tiles
             * @note X Y -> x and y position
             * @note q0 -> food quantity
             * @note q1 q2 q3 q4 q5 q6 -> rocks quantity
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
