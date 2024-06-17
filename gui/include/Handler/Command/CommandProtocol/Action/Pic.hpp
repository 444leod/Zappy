/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pic
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pic : public ICommand {
        public:
            /**
             * @brief The command Pic sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Pic receives when players are starting to incant
             * @note Receives the command: pic X Y L #n #n ...
             * @note X Y -> x and y position
             * @note L -> player level
             * @note #n -> player id
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
