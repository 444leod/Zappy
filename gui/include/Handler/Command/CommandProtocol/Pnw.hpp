/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pnw
*/

#pragma once

#include "../ACommand.hpp"

namespace gui {
    class Pnw : public ACommand {
        public:
            void stage(ntw::Client &client, std::string parameters = "") override;
            void receive(std::string command, GameData &gameData) override;

        private:
            std::map<std::string, Orientation> _orientationMap = {
                {"NORTH", Orientation::NORTH},
                {"EAST", Orientation::EAST},
                {"SOUTH", Orientation::SOUTH},
                {"WEST", Orientation::WEST}
            };
    };
}
