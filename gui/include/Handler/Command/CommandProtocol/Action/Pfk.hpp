/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pfk
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pfk : public ICommand {
        public:
            /**
             * @brief The command Pfk sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Pfk receives when a player start to lay an egg
             * @note Receives the command: pfk #n
             * @note #n -> player id
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
