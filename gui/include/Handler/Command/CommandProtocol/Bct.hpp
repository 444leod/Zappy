/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Bct
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Bct : public ACommand {
        public:
            void send(std::string command, ntw::Client &client) override;
            void receive(std::string command, GameData &gameData) override;

        protected:
        private:
    };
}
