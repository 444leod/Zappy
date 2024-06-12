/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Enw
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Enw : public ICommand {
        public:
            /**
             * @brief The command Enw send nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Enw receive when an egg is laid by a player
             * @note Receive the command: enw #e #n x y
             * @note #e -> egg id
             * @note #n -> player id
             * @note x y -> x and y position
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
