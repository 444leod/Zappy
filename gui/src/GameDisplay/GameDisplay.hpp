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
            ~GameDisplay() = default;

            /**
             * @brief Called once when the game is created. It should be used to
             *        load the textures.
             * @param lib the current library
             */
            void initialize(ILibrary& lib, GameData& gameData);

            /**
             * @brief Called when a key is pressed
             * @param event the event
             */
            void onKeyPressed(ILibrary& lib, KeyCode key, bool shift);

            /**
             * @brief Called when a mouse button is pressed
             * @param event the event
             */
            void onMouseButtonPressed(ILibrary& lib, MouseButton button, int32_t x, int32_t y);

            /**
             * @brief This function is called to draw the game. It should be used
             *        to draw based on the current game state and not do any logic.
             * @param lib the current library
             */
            void draw(ILibrary& lib, GameData& gameData);
    };
}
