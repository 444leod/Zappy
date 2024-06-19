/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Display
*/

#pragma once

#include "ILibrary.hpp"
#include "GameData.hpp"

namespace gui {

    class GameDisplay {
        public:
            /**
             * @brief Called once when the game is created. It should be used to
             *        load the textures.
             * @param lib the current library
             */
            void initialize(ILibrary& lib);

            /**
             * @brief This function is called to draw the game. It should be used
             *        to draw based on the current game state and not do any logic.
             * @param lib the current library
             * @param gameData the game data
             */
            void draw(ILibrary& lib, GameData& gameData);
    };
}
