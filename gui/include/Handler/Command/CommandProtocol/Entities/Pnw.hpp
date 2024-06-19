/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pnw
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pnw : public ICommand {
        public:
            /**
             * @brief The command Pnw sends nothing to the server
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command Pnw receives when a player is created
             * @note Receives the command: pnw #n x y o l n
             * @note #n -> player id
             * @note x y -> x and y position
             * @note o -> player orientation (NORTH, EAST, SOUTH, WEST)
             * @note l -> player level
             * @note n -> team name
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;

        private:
            std::map<std::string, Orientation> _stringToOrientation = {
                {"NORTH", Orientation::NORTH},
                {"EAST", Orientation::EAST},
                {"SOUTH", Orientation::SOUTH},
                {"WEST", Orientation::WEST}
            };
    };
}
