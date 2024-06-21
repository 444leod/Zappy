/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AEntity
*/

#pragma once

#include <cstdint>
#include "Orientation.hpp"
#include "Vector.hpp"
#include <vector>
#include <stack>
#include <memory>
#include "macros.hpp"
#include "Message.hpp"
#include "AAnimation.hpp"

/**
 * @brief Class representing entity in the simulation
 * @note Entity are the Players and the eggs in the simulation
*/
namespace gui {
    class AEntity {
        public:
            /**
             * @brief Construct a new AEntity object
            */
            AEntity() = default;

            /**
             * @brief Construct a new AEntity object
             * @param id Id of the entity
             * @param position Position of the entity
             * @param orientation Orientation of the entity
             * @param teamName Team name of the entity
            */
            AEntity(std::uint32_t id, Vector2u position, Orientation orientation, std::string teamName)
                : _position(position), _orientation(orientation), _id(id), _teamName(teamName) {}

            /**
             * @brief Construct a new AEntity object
             * @param id Id of the entity
             * @param position Position of the entity
            */
            AEntity(std::uint32_t id, Vector2u position, std::string teamName) : _position(position), _id(id), _teamName(teamName) {}

            /**
             * @brief Destroy the AEntity object
            */
            ~AEntity() = default;

            /**
             * @brief Set the entity Id
             * @param id Id of the entity
            */
            virtual void setId(std::uint32_t id) { this->_id = id; };

            /**
             * @brief Get the entity Id
             * @return std::uint32_t Id of the entity
            */
            virtual std::uint32_t id() const { return this->_id; };

            /**
             * @brief Set the orientation of the entity
             * @param orientation Orientation of the entity
             * @note The orientation can be NORTH, EAST, SOUTH, WEST
            */
            virtual void setOrientation(Orientation orientation) { this->_orientation = orientation; };

            /**
             * @brief Get the orientation of the entity
             * @return Orientation Orientation of the entity
            */
            virtual Orientation orientation() const { return this->_orientation; };

            /**
             * @brief Set the position of the entity
             * @param position Position of the entity
            */
            virtual void setPosition(Vector2u position) { this->_position = position; };

            /**
             * @brief Get the position of the entity
             * @return Vector2u Position of the entity
            */
            virtual Vector2u position() const { return this->_position; };

            /**
             * @brief Set the entity team name
             * @param teamName Team name of the entity
            */
            virtual void setTeamName(std::string teamName) { this->_teamName = teamName; };

            /**
             * @brief Get the entity team name
             * @return std::string Team name of the entity
            */
            virtual std::string teamName() const { return this->_teamName; };

            void pushAnimation(std::shared_ptr<gui::AAnimation> animation) { this->_animations.push(animation); }

            virtual void updateAnimation(float deltaTime) = 0;
            virtual void drawAnimation(ILibrary &lib) = 0;

            /**
             * @brief Set the display offset of the player (for animations)
             * @param offset The display offset of the player
             * @note The display offset is used to display the player at the right position
             *    when the player is moving for example
             */
            void setDisplayOffset(Vector2f offset) { this->_displayOffset = offset; }

            /**
             * @brief Get the display offset of the player
             * @return Vector2f The display offset of the player
             * @note The display offset is used to display the player at the right position
             *    when the player is moving for example
             */
            Vector2f displayOffset() const { return this->_displayOffset; }

            void setTileDisplayOffset(Vector2f offset) { this->_tileDisplayOffset = offset; }

            Vector2f tileDisplayOffset() const { return this->_tileDisplayOffset; }

            void setRandomOffset(Vector2f offset) { this->_randomOffset = offset; }

            Vector2f randomOffset() const { return this->_randomOffset; }

            void setSkin(std::string skin) { this->_skin = skin; }

            std::string skin() const { return this->_skin; }

            void setTeamColor(gui::Color color) { this->_teamColor = color; }

            gui::Color teamColor() const { return this->_teamColor; }

        protected:
            Vector2u _position = {0, 0};
            Orientation _orientation = Orientation::NORTH;
            std::uint32_t _id = 0;
            std::string _teamName = "";
            Vector2f _displayOffset = {0, 0};
            Vector2f _tileDisplayOffset = {0, 0};
            Vector2f _randomOffset = {0, 0};
            std::stack<std::shared_ptr<gui::AAnimation>> _animations = {};
            std::string _currentFrame = "";
            std::string _skin = "";
            gui::Color _teamColor = {255, 255, 255, 255};
    };
}
