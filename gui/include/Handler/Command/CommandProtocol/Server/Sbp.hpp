/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sbp
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Sbp : public ICommand {
        public:
            /**
             * @brief The command sbp sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command sbp receives when the server send a bad command
             * @note Receives the command: sbp
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
