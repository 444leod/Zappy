/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pbc
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pbc : public ICommand {
        public:
            /**
             * @brief The command Pbc sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Pbc receives when a player broadcast a message
             * @note Receives the command: pbc #n message
             * @note #n -> player id
             * @note message -> message
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
