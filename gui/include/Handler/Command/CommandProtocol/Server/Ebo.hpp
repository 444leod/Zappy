/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ebo
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Ebo : public ICommand {
        public:
            /**
             * @brief The command Ebo sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Ebo receives when there is a connection to an egg
             * @note Receives the command: ebo #e
             * @note #e -> egg id
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
