/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ppo
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Ppo : public ACommand {
        public:
            void send(std::string command, ntw::Client &client) override;
            void receive(std::string command, GameData &gameData) override;

        private:
            /**
             * @brief get the orientation based on a string
             * @param orientation The orientation
             * @return Orientation The orientation
            */
            Orientation getOrientationFromStr(std::string orientation);
    };
}
