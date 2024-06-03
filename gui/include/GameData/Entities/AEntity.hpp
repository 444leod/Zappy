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
            virtual void setEntityId(std::uint32_t id) { _id = id; };

            /**
             * @brief Get the entity Id
             * @return std::uint32_t Id of the entity
            */
            virtual std::uint32_t entityId() const { return _id; };

            /**
             * @brief Set the orientation of the entity
             * @param orientation Orientation of the entity
             * @note The orientation can be NORTH, EAST, SOUTH, WEST
            */
            virtual void setOrientation(Orientation orientation) { _orientation = orientation; };

            /**
             * @brief Get the orientation of the entity
             * @return Orientation Orientation of the entity
            */
            virtual Orientation orientation() const { return _orientation; };

            /**
             * @brief Set the position of the entity
             * @param position Position of the entity
            */
            virtual void setEntityPosition(Vector2i position) { _position = position; };

            /**
             * @brief Get the position of the entity
             * @return Vector2i Position of the entity
            */
            virtual Vector2i entityPosition() const { return _position; };

        protected:
            Vector2i _position = {0, 0};
            Orientation _orientation = Orientation::NORTH;
            std::uint32_t _id = 0;
    };
}