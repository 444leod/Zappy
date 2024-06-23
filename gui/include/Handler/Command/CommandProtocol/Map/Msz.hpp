/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Msz
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Msz : public ICommand {
        public:
            /**
             * @brief The command Msz sends simply "msz" to the server and expect the map size
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Msz receives the map size
             * @note Receives the command: msz X Y
             * @note X Y -> x and y size of the map
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
