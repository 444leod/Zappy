/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sgt
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Sgt : public ICommand {
        public:
            /**
             * @brief the command Sgt sends simply "sgt" to the server to get the time unit
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Sgt receives when the server send the time unit
             * @note Receives the command: sgt T
             * @note T -> time unit
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
