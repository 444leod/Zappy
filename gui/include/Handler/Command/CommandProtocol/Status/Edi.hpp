/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Edi
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Edi : public ICommand {
        public:
            /**
             * @brief The command Edi send nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Edi receive when the server send an egg that is dead
             * @note Receive the command: edi #e
             * @note #e -> egg id
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;
    };
}
