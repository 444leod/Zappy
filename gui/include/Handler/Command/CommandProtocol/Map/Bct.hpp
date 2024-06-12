/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Bct
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Bct : public ICommand {
        public:
            /**
             * @brief The command Bct send the position of the tile to the server and expect the content of the tile
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Bct receive the content of a tile
             * @note Receive the command: bct X Y q0 q1 q2 q3 q4 q5 q6
             * @note X Y -> x and y position
             * @note q0 -> food
             * @note q1 q2 q3 q4 q5 q6 -> rocks
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
