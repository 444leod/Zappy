/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Plv
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Plv : public ICommand {
        public:
            /**
             * @brief The command Plv sends the player id to the server and expect the level of the player
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Plv receives the level of a player
             * @note Receives the command: plv #n l
             * @note #n -> player id
             * @note l -> level
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
