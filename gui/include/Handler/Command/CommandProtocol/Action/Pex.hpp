/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pex
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pex : public ICommand {
        public:
            /**
             * @brief The command Pex sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Pex receives when a player is expulsed from a tile
             * @note Receives the command: pex #n
             * @note #n -> player id
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
