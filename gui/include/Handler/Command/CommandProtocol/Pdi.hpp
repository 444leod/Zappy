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
            void stage(ntw::Client &client, std::string parameters = "") override;
            void receive(std::string command, GameData &gameData) override;

        protected:
        private:
    };
}
