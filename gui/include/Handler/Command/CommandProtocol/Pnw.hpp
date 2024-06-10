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
            void send() override;
            void receive(std::string command, GameData &gameData) override;

            /**
             * @brief get the orientation based on a string
             * @param orientation The orientation
             * @return Orientation The orientation
            */
            Orientation getOrientationFromStr(std::string orientation);

        protected:
        private:
    };
}