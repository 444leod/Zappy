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

            /**
             * @brief Draw the map
             * @param lib the current library
             * @param gameData the game data
             */
            void drawMap(ILibrary& lib, GameData& gameData);

            /**
             * @brief Draw the map content
             * @param lib the current library
             * @param data the game data
             */
            void drawMapContent(ILibrary &lib, GameData& data);

            /**
             * @brief Draw a single map tile
             * @param lib the current library
             * @param x the x position of the tile
             * @param y the y position of the tile
             */
            void drawMapTile(ILibrary& lib, std::uint32_t x, std::uint32_t y);

            /**
             * @brief Draw the players
             * @param lib the current library
             * @param gameData the game data
             */
            void drawPlayers(ILibrary& lib, GameData& gameData);

            /**
             * @brief Draw the eggs
             * @param lib the current library
             * @param gameData the game data
             */
            void drawEggs(ILibrary& lib, GameData& gameData);

            /**
             * @brief Draw the rocks
             * @param lib the current library
             * @param tileContent the tile content
             * @param coordinates the coordinates of the tile
             */
            void drawRocks(ILibrary& lib, TileContent& tileContent, Vector2u coordinates);

            /**
             * @brief Draw the food
             * @param lib the current library
             * @param tileContent the tile content
             * @param coordinates the coordinates of the tile
             */
            void drawFood(ILibrary& lib, TileContent& tileContent, Vector2u coordinates);

            /**
             * @brief Draw the messages
             * @param lib the current library
             * @param gameData the game data
             */
            void drawMessages(ILibrary& lib, GameData& gameData);

            /**
             * @brief Draw the team names
             * @param lib the current library
             * @param gameData the game data
             */
            void drawTeamNames(ILibrary& lib, GameData& gameData);

        private:
            bool _initialized = false;
            gui::Vector2i _firstTileOffset = {0, 0};
    };
}
