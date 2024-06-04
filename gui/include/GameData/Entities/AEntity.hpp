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

/**
 * @brief Class representing entity in the simulation
 * @note Entity are the characters and the eggs in the simulation
*/
namespace gui {
    class AEntity {
        public:
            /**
             * @brief Construct a new AEntity object
            */
            AEntity() = default;

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

        protected:
            Vector2u _position = {0, 0};
            Orientation _orientation = Orientation::NORTH;
            std::uint32_t _id = 0;
            std::string _teamName = "";
    };
}