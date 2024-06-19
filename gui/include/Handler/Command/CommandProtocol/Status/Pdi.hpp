/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdi
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pdi : public ICommand {
        public:
            /**
             * @brief The command pdi sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command pdi receives when a player die
             * @note Receives the command: pdi #n
             * @note #n -> player id
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
