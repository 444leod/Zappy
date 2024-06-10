/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pdi
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Pdi : public ACommand {
        public:
            void send(std::string command, ntw::Client &client) override;
            void receive(std::string command, GameData &gameData) override;

        protected:
        private:
    };
}