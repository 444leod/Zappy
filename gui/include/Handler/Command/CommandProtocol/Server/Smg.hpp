/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Smg
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Smg : public ICommand {
        public:
            /**
             * @brief The command Smg sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Smg receives when the server send a message
             * @note Receives the command: smg M
             * @note M -> message
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
