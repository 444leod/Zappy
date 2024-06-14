/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ppo
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Ppo : public ICommand {
        public:
            /**
             * @brief The command Ppo sends the player id to the server and expect the orientation of the player
             * @param client The client
             * @param parameters The parameters
            */
            void stage(ntw::Client &client, std::string parameters = "") override;

            /**
             * @brief The command Ppo receives the orientation of a player
             * @note Receives the command: ppo #n x y o
             * @note #n -> player id
             * @note x y -> x and y position
             * @note o -> player orientation (NORTH, EAST, SOUTH, WEST)
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, GameData &gameData) override;

        private:
            std::map<std::string, Orientation> _stringToOrientation = {
                {"NORTH", Orientation::NORTH},
                {"EAST", Orientation::EAST},
                {"SOUTH", Orientation::SOUTH},
                {"WEST", Orientation::WEST}
            };
    };
}
