/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pgt
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pgt : public ICommand {
        public:
            /**
             * @brief The command Enw send nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Pgt receive when a player take an item
             * @note Receive the command: pgt #n i
             * @note #n -> player id
             * @note i -> item number
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
