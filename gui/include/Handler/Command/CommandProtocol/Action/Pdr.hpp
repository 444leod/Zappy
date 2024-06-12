/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdr
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pdr : public ICommand {
        public:
            /**
             * @brief The command Pdr send nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Pdr receive when a player drop an item
             * @note Receive the command: pdr #n i
             * @note #n -> player id
             * @note i -> item number
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
