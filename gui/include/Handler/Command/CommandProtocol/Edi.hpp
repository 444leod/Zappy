/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Edi
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Edi : public ACommand {
        public:
            void stage(ntw::Client &client, std::string command) override;
            void receive(std::string command, GameData &gameData) override;

        protected:
        private:
    };
}
