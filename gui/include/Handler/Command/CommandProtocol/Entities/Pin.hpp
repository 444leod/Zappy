/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pin
*/

#pragma once

#include "../ICommand.hpp"

namespace gui {
    class Pin : public ICommand {
        public:
            /**
             * @brief The command Pin sends: pin #n
             * @note #n -> player id
             * @param client The client
             * @param parameters The parameters
            */
            void stage(std::shared_ptr<ntw::Client> client, std::string parameters = "") override;

            /**
             * @brief The command gets the player's inventory
             * @note Receives the command: pin #n x y q0 q1 q2 q3 q4 q5 q6
             * @note #n -> player id
             * @note x y -> x and y position
             * @note q0 -> food
             * @note q1 q2 q3 q4 q5 q6 -> stones
             * @param command The command given by the server
             * @param gameData The game data
            */
            void receive(std::string command, std::shared_ptr<GameData> gameData) override;
    };
}
